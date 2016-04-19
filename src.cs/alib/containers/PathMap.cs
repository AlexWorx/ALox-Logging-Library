// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;
using System.Collections.Generic;
using System;



/** ************************************************************************************************
 * This namespace of the A-Worx Library holds classes that are implementing (generic) containers.
 **************************************************************************************************/
namespace cs.aworx.lib.containers  {



/** ************************************************************************************************
 * This class implements a map suitable for keys that are hierarchically organized.
 * While the class works with any type of keys, it is efficient only if keys are rather
 * long and similar to each other. A good example for such similar, hierarchical keys are
 * file path names.<br>
 * Each portion of any key inserted is stored only once. The insert and receive operations
 * (both performed with method #Get) are performed in O(<key length>).
 *
 * \note
 *   This class is not considered as complete and final in the current version of %ALib.
 *   The functionality currently is restricted to the needs of %ALox logging library.
 **************************************************************************************************/
public class PathMap<StoreT>
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
        /** Our parent, if empty, we are root. Attention: The parent might not be identical to
         *  the object that lists us in its #Childs vector. This is true, when an associated
         *  value is not to be used in the parent.
         */
        public PathMap<StoreT>                        Parent;

        /** The portion of the path represented */
        public AString                                Path                          = new AString();

        /** The value carried by this object */
        public StoreT                                 Value                       = default(StoreT);

        /** A list of children. */
        public List<PathMap<StoreT>>                  Childs          = new List<PathMap<StoreT>>();

    // #############################################################################################
    // Public interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructor
         * @param   parent  Our parent node.
         ******************************************************************************************/
        public PathMap( PathMap<StoreT> parent= null )
        {
            this.Parent= parent;
        }

        /** ****************************************************************************************
         * Clears all data stored, resets all values.
         ******************************************************************************************/
        public void Clear()
        {
            Childs.Clear();
            Value=  default(StoreT);
        }

        /** ****************************************************************************************
         * Gets a node. If not existent and parameter \p create is \c true, the node is created.
         * @param   key        The key to the stored value.
         * @param   create     Flag if a non-existent entry should be created.
         * @param   separators A list of characters recognized as separators.
         * @return Returns the ourselves or a child node representing the key string.
         ******************************************************************************************/
        public PathMap<StoreT>  Get   ( Substring  key,  bool create,  AString separators )
        {
            PathMap<StoreT> node= get( key, create, separators );
            return node != null ? node : this;
        }

        /** ****************************************************************************************
         * Removes a node.
         * @param  node  The node to remove.
         ******************************************************************************************/
        public void     Remove ( PathMap<StoreT> node )
        {
            // we are lazy and do not remove the node. Its value just gets nulled
            node.Value= default(StoreT);
        }



    // #############################################################################################
    // Enumeration interface
    // #############################################################################################

        /** Simple pair of a map and its current child */
        class NodeAndChild
        {
            public PathMap<StoreT>      node;       ///< A node to remember.
            public int                  childNo;    ///< The current child of the node.

            /** Constructor
             *  @param node     The node to store.
             *  @param childNo  The current child within \p node.
             */
            public NodeAndChild(PathMap<StoreT> node, int childNo)
            {
                this.node=      node;
                this.childNo=   childNo;
            }
        };

        /** ****************************************************************************************
         * Enumerator using a DFS strategy.
         * @return <b>Yield returns</b> the list of nodes.
         ******************************************************************************************/
        public IEnumerator<PathMap<StoreT>> GetEnumerator() 
        {
            Stack<NodeAndChild>  nodesAndChilds  =new Stack<NodeAndChild>();
            nodesAndChilds.Push( new NodeAndChild( this, -2) );

            while(nodesAndChilds.Count > 0 )
            {
                NodeAndChild top= nodesAndChilds.Peek();
                top.childNo++;

                if ( top.childNo >= nodesAndChilds.Peek().node.Childs.Count )
                {
                    nodesAndChilds.Pop();
                    continue;
                }
                else if ( top.childNo >= 0 )
                {
                    nodesAndChilds.Push( top= new NodeAndChild( top.node.Childs[top.childNo], -1 ) );
                }


                if ( top.node.Value != null  )
                    yield return top.node;
            }
        }

    // #############################################################################################
    // Protected interface
    // #############################################################################################
    
        /** ****************************************************************************************
         * Gets a node. If not existent and parameter \p create is \c true, the node is created.
         * @param   key        The key to the stored value.
         * @param   create     Flag if a non-existent entry should be created.
         * @param   separators A list of characters recognized as separators.
         * @return Returns the ourselves or a child node representing the key string.
         ******************************************************************************************/
        protected PathMap<StoreT>    get    ( Substring  key,  bool create, AString separators )
        {
            int idx= 0;
            int pLen= Path.Length();
            if ( pLen > 0 )
            {
                int cmpLen= pLen < key.Length() ? pLen : key.Length();
                char[] kBuf=    key.Buf;
                char[] pBuf=    Path.Buffer();

                while( idx < cmpLen && kBuf[ key.Start + idx] == pBuf[idx] )
                    idx++;

                key.Consume( idx );
            }

            // all of 'our' path characters matched
            if( idx == pLen)
            {
                // identical to the searched string?
                if( key.IsEmpty() )
                    return this;

                // return matching child
                foreach ( PathMap<StoreT> child in Childs )
                {
                    if( key.CharAtStart() == child.Path.CharAtStart() )
                    {
                        PathMap<StoreT> search= child.get( key, create, separators );
                        if ( search != null )
                            return search;
                    }
                }

                // no child found
                if(create)
                {
                    PathMap<StoreT> newChild= null;
                    newChild= new PathMap<StoreT>( this );
                    newChild.Path._( key );
                    Childs.Add( newChild );
                    return newChild;
                }
            }

            // nothing matched
            else if ( idx == 0 )
                return null;


            // just a part of us matched
            else if ( create )
            {
                // create new child receiving our old path (rest), our value and childs
                PathMap<StoreT> child1= new PathMap<StoreT>( this );
                child1.Path._( Path, idx );

                List<PathMap<StoreT>> tempList= child1.Childs;
                foreach( PathMap<StoreT> child in Childs )
                    child.Parent= child1;
                child1.Childs= Childs;   
                Childs= tempList;

                child1.Value=  Value;
                Childs.Clear();
                Childs.Add( child1 );

                // cut my path and clear my value
                Path.SetLength_NC( idx );
                Value= default(StoreT);

                // create second child if remaining path is not empty
                if( key.IsNotEmpty() )
                {
                    PathMap<StoreT> child2= new PathMap<StoreT>( this );
                    child2.Path._( key );

                    Childs.Add( child2 );
                    return child2;
                }

                return this;
            }

            // return us, or if this is not a real node, our parent
            if( Parent == null || idx == 0 ||  separators.IndexOf( Path.CharAt_NC( idx - 1 ) ) >= 0 )
                return this;
            else
                return Parent;
        }

}

} // namespace / EOF
