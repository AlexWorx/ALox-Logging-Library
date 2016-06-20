// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


/** ************************************************************************************************
 * This package of the A-Worx Library holds classes that are implementing (generic) containers.
 **************************************************************************************************/
package com.aworx.lib.containers;

import java.util.ArrayList;
import java.util.Deque;
import java.util.Iterator;
import java.util.LinkedList;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;


/** ************************************************************************************************
 * This class implements a map suitable for keys that are hierarchically organized.
 * While the class works with any type of keys, it is efficient only if keys are rather
 * long and similar to each other. 
 * Each portion of any key inserted is stored only once.
 *
 * \note
 *   This class is not considered as complete and final in the current version of %ALib.
 *   The functionality currently is restricted to the needs of %ALox logging library.
 **************************************************************************************************/
public class PathMap<StoreT> implements Iterable<PathMap<StoreT>> 
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
        /** Our parent, if empty, we are root. Attention: The parent might not be identical to
         *  the object that lists us in its #childs vector. This is true, when an associated
         *  value is not to be used in the parent.
         */
        public PathMap<StoreT>                        parent; 

        /** The portion of the path represented */
        public AString                                path                          = new AString();

        /** The value carried by this object */
        public StoreT                                 value                                  = null;

        /** A list of children. */
        public ArrayList<PathMap<StoreT>>             childs     = new ArrayList<PathMap<StoreT>>();

    // #############################################################################################
    // Public interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructor
         ******************************************************************************************/
        public PathMap()
        {
            this.parent= null;
        }

        /** ****************************************************************************************
         * Constructor
         * @param   parent  Our parent node.
         ******************************************************************************************/
        public PathMap( PathMap<StoreT> parent)
        {
            this.parent= parent;
        }

        /** ****************************************************************************************
         * Clears all data stored, resets all values.
         ******************************************************************************************/
        public void clear()
        {
            childs.clear();
            value=  null;
        }

        /** ****************************************************************************************
         * Gets a node. If not existent and parameter \p create is \c true, the node is created.
         * @param   key        The key to the stored value.
         * @param   create     Flag if a non-existent entry should be created.
         * @param   separators A list of characters recognized as separators.
         * @return Returns the ourselves or a child node representing the key string.
         ******************************************************************************************/
        public PathMap<StoreT>  Get   ( Substring  key,  boolean create,  AString separators )
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
            node.value= null;
        }



    // #############################################################################################
    // Enumeration interface
    // #############################################################################################

        /** ****************************************************************************************
         * Enumerator using a DFS strategy.
         * @return <b>Yield returns</b> the list of nodes.
         ******************************************************************************************/
        class MyIterator implements Iterator<PathMap<StoreT>>
        {
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
    

            /** A stack holding the recursive list of child maps and the  idx of their current child */
            Deque<NodeAndChild>  nodesAndChilds  = null;

            /** Constructor 
             * @param initialNode The node to start the iteration on.
             */ 
            public MyIterator( PathMap<StoreT> initialNode )
            {
                nodesAndChilds= new LinkedList<NodeAndChild>();
                nodesAndChilds.push( new NodeAndChild( initialNode, -2) );
                forward();
            }

            /** Implementation of iterator interface
             * @return \c true if a next element is available, \c false else */
            @Override
            public boolean hasNext() 
            {
                return nodesAndChilds.size() != 0;
            }

            /** Implementation of iterator interface
             * @return \c The next element */
            @Override
            public PathMap<StoreT> next() 
            {
                 PathMap<StoreT> returnValue= nodesAndChilds.peek().node;
                 forward();
                 return returnValue;
            }

            /** Implementation of iterator interface
             * @return \c The next element */
            void forward() 
            {
                while(nodesAndChilds.size() > 0 )
                {
                    NodeAndChild top= nodesAndChilds.peek();
                    top.childNo++;
    
                    if ( top.childNo >= nodesAndChilds.peek().node.childs.size() )
                    {
                        nodesAndChilds.pop();
                        continue;
                    }
                    else if ( top.childNo >= 0 )
                    {
                        nodesAndChilds.push( top= new NodeAndChild( top.node.childs.get(top.childNo), -1 ) );
                    }
    
                    if ( top.node.value != null  )
                        return;
                }
            }

            /** Not supported for this iterator. Throws \c UnsupportedOperationException. */
            @Override
            public void remove() 
            {
                throw new UnsupportedOperationException();
            }
        };

        /** ****************************************************************************************
         * Enumerator using a DFS strategy.
         * @return <b>Yield returns</b> the list of nodes.
         ******************************************************************************************/
        @Override public Iterator<PathMap<StoreT>> iterator()
        {
            return new MyIterator( this ); 
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
        protected PathMap<StoreT>    get    ( Substring  key,  boolean create, AString separators )
        {
            // find the index of the match length and consume these characters from the key
            int idx= 0;
            int pLen= path.length();
            if ( pLen > 0 )
            {
                int cmpLen= pLen < key.length() ? pLen : key.length();
                char[] kBuf=    key.buf;
                char[] pBuf=    path.buffer();

                while( idx < cmpLen && kBuf[ key.start + idx] == pBuf[idx] )
                    idx++;

                key.consume( idx );
            }

            // all of 'our' path characters matched
            if( idx == pLen)
            {
                // identical to the searched string?
                if( key.isEmpty() )
                    return this;

                // return matching child
                for ( PathMap<StoreT> child : childs )
                {
                    if( key.charAtStart() == child.path.charAtStart() )
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
                    newChild.path._( key );
                    childs.add( newChild );
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
                child1.path._( path, idx );

                ArrayList<PathMap<StoreT>> tempList= child1.childs;
                for( PathMap<StoreT> child : childs )
                    child.parent= child1;
                child1.childs= childs;   
                childs= tempList;

                child1.value=  value;
                childs.clear();
                childs.add( child1 );

                // cut my path and clear my value
                path.setLength_NC( idx );
                value= null;

                // create second child if remaining path is not empty
                if( key.isNotEmpty() )
                {
                    PathMap<StoreT> child2= new PathMap<StoreT>( this );
                    child2.path._( key );

                    childs.add( child2 );
                    return child2;
                }

                return this;
            }

            // return if this is the root or a real node
            if( parent == null ||  separators.indexOf( path.charAt_NC( idx - 1 ) ) >= 0 )
                return this;
            return parent;
        }
}
