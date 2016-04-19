// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_CONTAINERS_PATHMAP)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_CONTAINERS_PATHMAP
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_CONTAINERS_PATHMAP 1
#endif



// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_STRINGS_ASSUBSTRING)
    #include "alib/strings/substring.hpp"
#endif
#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif


namespace aworx {
namespace           lib {

/** ************************************************************************************************
 * This namespace of the A-Worx Library holds classes that are implementing (generic) containers.
 **************************************************************************************************/
namespace                   containers {

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
template<typename StoreT>
class PathMap
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /** Our parent, if empty, we are root. Attention: The parent might not be identical to
         *  the object that lists us in its #Childs vector. This is true, when an associated
         *  value is not to be used in the parent.
         */
        PathMap*                               Parent;

        /** The portion of the path represented */
        AString                                Path;

        /** The value carried by this object */
        StoreT                                 Value;

        /** A list of children. */
        std::vector<PathMap*>                  Childs;

    // #############################################################################################
    // Public interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Constructor
         * @param   parent  Our parent node.
         ******************************************************************************************/
        PathMap(PathMap* parent= nullptr)
        : Parent(parent)
        , Value(0)
        {
        }


        /** ****************************************************************************************
         * Destructor
         ******************************************************************************************/
        ~PathMap()
        {
            for ( auto child : Childs )
                delete child;
        }

        /** ****************************************************************************************
         * Clears all data stored, resets all values.
         ******************************************************************************************/
        void Clear()
        {
            ALIB_ASSERT( Value == 0 );
            ALIB_ASSERT( Path.IsEmpty() );

            for ( auto child : Childs )
                delete child;

            Childs.clear();
        }


        /** ****************************************************************************************
         * Gets a node. If not existent and parameter \p create is \c true, the node is created.
         * @param   key        The key to the stored value.
         * @param   create     Flag if a non-existent entry should be created.
         * @param   separators A list of characters recognized as separators.
         * @return Returns the ourselves or a child node representing the key string.
         ******************************************************************************************/
        PathMap*    Get    ( const TString&  key,  bool create, const TString& separators )
        {
            Substring p( key );
            PathMap<StoreT>* node= get( p, create, separators );
            return node != nullptr ? node : this;
        }

        /** ****************************************************************************************
         * Removes a node.
         * @param  node  The node to remove.
         ******************************************************************************************/
        void     Remove ( PathMap* node )
        {
            // we are lazy and do not remove the node. Its value just gets nulled
            node->Value= 0;
        }


    // #############################################################################################
    // Protected interface
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         * Gets a node. If not existent and parameter \p create is \c true, the node is created.
         * @param   key        The key to the stored value.
         * @param   create     Flag if a non-existent entry should be created.
         * @param   separators A list of characters recognized as separators.
         * @return Returns the ourselves or a child node representing the key string.
         ******************************************************************************************/
        PathMap*    get    ( Substring&  key,  bool create, const TString& separators )
        {
            // find the index of the match length and consume these characters from the key
            int idx= 0;
            int pLen= Path.Length();
            if ( pLen > 0 )
            {
                int cmpLen= pLen < key.Length() ? pLen : key.Length();
                const char* kBuf=    key.Buffer();
                const char* pBuf=    Path.Buffer();

                while( idx < cmpLen && *(kBuf + idx) == *(pBuf +idx ) )
                    idx++;

                key.Consume<false>( idx );
            }

            // all of 'our' path characters matched
            if( idx == pLen)
            {
                // identical to the searched string?
                if( key.IsEmpty() )
                    return this;

                // return matching child
                for ( auto child : Childs )
                {
                    if( key.CharAtStart<false>() == child->Path.CharAtStart() )
                    {
                        PathMap* search= child->get( key, create, separators );
                        if ( search != nullptr )
                            return search;
                    }
                }

                // no child found
                if(create)
                {
                    PathMap* newChild= nullptr;
                    newChild= new PathMap( this );
                    newChild->Path._( key );
                    Childs.emplace_back( newChild );
                    return newChild;
                }
            }

            // nothing matched
            else if ( idx == 0 )
                return nullptr;


            // just a part of us matched
            else if ( create )
            {
                // create new child receiving our old path (rest), our value and childs
                PathMap* child1= new PathMap( this );
                child1->Path._( Path, idx );

                for( auto child : Childs )
                    child->Parent= child1;

                child1->Childs= Childs;
                child1->Value=  Value;
                Childs.clear();
                Childs.emplace_back( child1 );

                // cut my path and clear my value
                Path.SetLength<false>( idx );
                Value= 0;

                // create second child if remaining path is not empty
                if( key.IsNotEmpty() )
                {
                    PathMap* child2= new PathMap( this );
                    child2->Path._( key );

                    Childs.emplace_back( child2 );
                    return child2;
                }

                return this;
            }

            // return us, or if this is not a real node, our parent
            if( Parent == nullptr || idx == 0 ||  separators.IndexOf( Path.CharAt<false>( idx - 1 ) ) >= 0 )
                return this;
            else
                return Parent;
        }

    /** ************************************************************************************************
     * This inner class implements a \c std::iterator using a DFS strategy.
     **************************************************************************************************/
    public:
    class Iterator : public std::iterator<std::input_iterator_tag, StoreT>
    {
        private:
            /** Simple pair of a map and its current child */
            struct NodeAndChild
            {
                const PathMap<StoreT>*     node;       ///< A node to remember.
                int                         childNo;    ///< The current child of the node.

                /** Constructor
                 *  @param node     The node to store.
                 *  @param childNo  The current child within \p node.
                 */
                NodeAndChild(const PathMap<StoreT>* node, int childNo) : node(node), childNo(childNo) {}
            };

            /** A stack holding the recursive list of child maps and the  idx of their current child */
            std::stack<NodeAndChild>                    nodesAndChilds;

        public:
            /** Standard constructor, used to create and \c end() iterator  */
            Iterator()
            {
            }

            /** Constructor
             *  @param sm  The tree map to iterate on.
             */
            Iterator(const PathMap<StoreT> &sm)
            {
                nodesAndChilds.push( NodeAndChild(&sm, -2) );
                ++(*this);
            }

            /** Comparison operator.
             *  @param other  The object to compare ourselves to.
             *  @return \c true if this and given iterator are equal, \c false otherwise. */
            bool operator==(const typename PathMap<StoreT>::Iterator &other) const
            {
                if ( nodesAndChilds.size() == 0 || other.nodesAndChilds.size() == 0)
                    return nodesAndChilds.size() == other.nodesAndChilds.size();


                return      this->nodesAndChilds.top().node    == other.nodesAndChilds.top().node
                        &&  this->nodesAndChilds.top().childNo == other.nodesAndChilds.top().childNo;
            }

            /** Comparison operator.
             *  @param other  The object to compare ourselves to.
             *  @return \c false if this and given iterator are equal, \c true otherwise. */
            bool operator!=(const Iterator &other) const
            {
                return !(*this == other );
            }

            /** Retrieves the current PathMap node.
             * @return The current PathMap node.              */
            const PathMap<StoreT>& operator*() const
            {
                return *nodesAndChilds.top().node;
            }

            /** Increment operator.
             *  @return A reference to ourselves. */
            Iterator& operator++()
            {
                while(nodesAndChilds.size() > 0 )
                {
                    int child= ++nodesAndChilds.top().childNo;

                    if ( child >= (int) nodesAndChilds.top().node->Childs.size() )
                    {
                        nodesAndChilds.pop();
                        continue;
                    }
                    else if ( child >= 0 )
                    {
                        nodesAndChilds.push( NodeAndChild( nodesAndChilds.top().node->Childs[child], -1 ) );
                    }

                    if ( nodesAndChilds.top().node->Value != 0 )
                        return *this;
                }

               return *this;
            }

    };  // Iterator


}; // PathMap


/** Creates an iterator on the given \b %PathMap.
 * @param pathMap The object to iterate.
 * @return The iterator */
template<typename StoreT>
typename PathMap<StoreT>::Iterator begin(const PathMap<StoreT>& pathMap ) { return typename PathMap<StoreT>::Iterator( pathMap ); }

/** Creates an empty iterator. The given \b %PathMap is ignored.
 *  @return The iterator */
template<typename StoreT>
typename PathMap<StoreT>::Iterator end(const PathMap<StoreT>&            ) { return typename PathMap<StoreT>::Iterator(  );         }

}}// namespace lib::containers

/** Type alias name in namespace #aworx. */
template<typename StoreT>
using  PathMap=    aworx::lib::containers::PathMap<StoreT>;


} // namespace aworx



#endif // HPP_ALIB_CONTAINERS_PATHMAP
