// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


/** ************************************************************************************************
 * This \alib namespace holds rather simple utility classes which on the one hand do not
 * 'deserve' to be placed in a separated own namespace and on the other hand are not close enough
 * to the C++ language to be placed in namespace \ref com.aworx.lib.lang.
 **************************************************************************************************/
package com.aworx.lib.util;

import com.aworx.lib.lang.*;
import com.aworx.lib.ALIB_DBG;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;

import java.util.*;


/** ************************************************************************************************
 * This class manages an object of internal type
 * \ref com.aworx.lib.util.StringTree.Node "Node", which consists of
 * - A value of custom (template) type \p T,
 * - A pointer to a parent \b %Node and
 * - A hash table which recursively stores pointers to \b Node objects, referred to by
 *   a string-type key.
 *
 * This recursive data structure is what comprises a graph with named edges. As this object does
 * not allow insertion of nodes with circular dependencies, the graph is of tree type.
 * The way from the root node to the leafs usually is called "path" and the class incorporates
 * functionality to work with string representations of such paths where names of edges are
 * concatenated and separated by a special separation character.
 * Now, this explains why this class is called \b %StringTree.
 *
 * The search and creation of tree nodes by using aforementioned path strings, is very similar to
 * what is well known from addressing files and folders in file systems.
 * The difference is however, that this class does not differentiate between 'folders' and 'files',
 * hence between 'nodes' and 'leafs'. Every node has the same value type \p T and may or may not
 * have child nodes.
 * If such differentiation - or other semantics - is wanted, this may be modeled in custom
 * attributes provided in template type \p T.
 *
 * The internal node structure is not exposed publically and the class has no direct interface to
 * manipulate nodes. Instead, the interface is defined by two public inner types.
 * Those are:
 * - \ref com.aworx.lib.util.StringTree.Cursor       "Cursor" and
 * - \ref com.aworx.lib.util.StringTree.Walker       "Walker".
 *
 * and are explained in the following paragraphs.
 *
 * \note The C++ version of this class provides a third type \b  StdIterator
 *
 * \anchor java_alib_containers_stringtree_cursor
 * <b>Inner class %Cursor: Inserting, Retrieving And Deleting Nodes</b><br>
 * The class has no direct interface to manipulate nodes. The main interface into
 * objects of this type is defined by public, inner type
 * \ref com.aworx.lib.util.StringTree.Cursor "Cursor". The only way to create an
 * initial cursor is with method #root, which creates a cursor object referring to the
 * root node of the tree. With this, string names and complete paths can be used to
 * move the cursor along existing nodes of the tree or to create new child nodes or a whole
 * path of children at once.
 * Class cursor is quite lightweight as it contains just two pointers (to the \b %StringTree and the current node).
 * Hence, cursors can be cloned, assigned and passed around very efficiently.
 *
 * Once a cursor is created it can traverse over the tree nodes using methods
 * - \ref com.aworx.lib.util.StringTree.Cursor.moveToChild        "Cursor.moveToChild",
 * - \ref com.aworx.lib.util.StringTree.Cursor.moveToParent       "Cursor.moveToParent",
 * - \ref com.aworx.lib.util.StringTree.Cursor.moveTo             "Cursor.moveTo" and
 * - \ref com.aworx.lib.util.StringTree.Cursor.moveToExistingPart "Cursor.moveToExistingPart".
 *
 * For the creation of new child nodes or a complete path of such, methods
 * - \ref com.aworx.lib.util.StringTree.Cursor.moveToChildCreate              "Cursor.moveToChildCreate" and
 * - \ref com.aworx.lib.util.StringTree.Cursor.moveToAndCreateNonExistingPart "Cursor.moveToAndCreateNonExistingPart"
 *
 * are provided. Then, two methods for erasing nodes exist:
 * - \ref com.aworx.lib.util.StringTree.Cursor.deleteChild    "Cursor.deleteChild" and
 * - \ref com.aworx.lib.util.StringTree.Cursor.deleteChildren "Cursor.deleteChildren"
 *
 * Finally, class cursor can also be used like an iterator. But it explicitly and for good reason
 * does \b not follow the iteration concepts provided with Java. The iteration
 * feature comes with methods
 * - \ref com.aworx.lib.util.StringTree.Cursor.moveToParentUnchecked "Cursor.moveToParentUnchecked" and
 * - \ref com.aworx.lib.util.StringTree.Cursor.isValid               "Cursor.isValid".
 *
 * The first transitions the cursor to refer to the parent node. Using this method is (almost)
 * the only way how a cursor can get invalidated. Hence a simple loop can be written that visits
 * all nodes from a starting node, up to the root of the tree until \b %Cursor.IsValid evaluates
 * to \c false.
 *
 * <b>Inner class %Walker: Sorted Iterations</b><br>
 * Finally, with
 * \ref com.aworx.lib.util.StringTree.Walker "Walker", a third \b %StdIterator class is exposed.
 * The rational for having this class is to provide a configurable and controlled way of iterating
 * a tree or a branch. Some features of the class are:
 * - Can be created from (or reset to) the \b %StringTree itself,
 *   \ref com.aworx.lib.util.StringTree.Cursor "Cursor" objects.
 * - Can work recursively (with depth limitation) or just on the current nodes' direct children.
 * - Has several sort options:
 *   - built-in by path name, ascending/descending, case sensitive or ignoring
 *   - user defined by path name
 *   - user defined by template type
 *
 * The class is rather 'heavy' and recursive iteration needs to allocate memory for a sorted vector
 * of child nodes.
 * Therefore it is recommended to reuse instances of the class with subsequent, similar iterations.
 *
 * \anchor java_alib_containers_stringtree_iterator
 * <b>Recursive Iteration</b><br>
 *
 * Class \b %Walker supports recursive iteration.
 * Recursiveness is controlled with method
 * \ref com.aworx.lib.util.StringTree.Walker.setRecursionDepth "Walker.setRecursionDepth".
 * When the recursive iteration depth is limited, then the very first node (the root node of the
 * iteration) is skipped. With unlimited recursion, the root node is included (as the first
 * result). In the case, that the root node should not be included in an unlimited, recursive
 * iteration, it has to be skipped 'manually'.
 *
 * <b>Iterators And Changes Of The Underlying Container</b><br>
 * Objects of types
 * \ref com.aworx.lib.util.StringTree.Cursor "Cursor" and
 * \ref com.aworx.lib.util.StringTree.Walker "Walker" may become invalid when
 * the underlying \b %StringTree object changes and have to be re-initialized after such change.
 * I.e, there is no guarantee given that changes in the tree are not invalidating instances that
 * represent 'higher' nodes or or 'sibling' branches of those which have undergone changes.
 * Such invalid state can not be detected. As a result, the objects have to be reset or disposed on
 * changes of the tree.
 *
 * @tparam T   The value type of elements stored in the nodes of the tree.
 **************************************************************************************************/
public class StringTree<T>
{
    // #############################################################################################
    // Inner class Node
    // #############################################################################################

        /** The root node. */
        protected Node         root;

        /** The separator character using with path arguments of interface methods. */
        protected char         separator;


        /**
         * The internal, protected data structure implementing a node of the tree. This class is
         * not accessible from outside. Instead, inner class
         * \ref com.aworx.lib.util.StringTree.Cursor "Cursor", which represents node objects,
         * provides an indirect interface to the values of this class.
         */
        public class Node
        {
            /** Parent node. */
            public Node                       parent;

            /** Child nodes. */
            public HashMap<String, Node>      children;

            /** The template type value. */
            public T                          value;

            /**
             * Constructor.
             * @param _parent The parent of this node.
             */
            public Node( Node _parent )
            {
                parent= _parent;
                children = new HashMap<String, Node>();
                // value = default(T);
            }

            /**
             * Recursively calculates the depth of a node.
             * @return The depth of the this node.
             */
            public int depth()
            {
                int result= -1;
                Node p= this;
                while( p != null )
                {
                    result++;
                    p= p.parent;
                }
                return result;
            }

            /**
             * Returns \c true if this is the root node, \c false otherwise.
             * @return \c true if this is the root node, \c false otherwise.
             */
            public boolean isRoot()
            {
                return parent == null;
            }

            /**
             * Returns a child node identified by parameter \p childName.
             * If the child is not found or is illegal (empty, <c>"."</c> or <c>".."</c>
             * or contain a separator character), \c null is returned.
             * In debug compilations, an \ref com.aworx.lib.ALIB_DBG.WARNING "ALIB_DBG.WARNING"
             * is reported on illegal child names.
             *
             * @param  childName The name of the child
             * @param  separator The path separator.
             * @return The child node found, \c null on failure.
             */
            public Node getChild( String childName, char separator )
            {
                if(    childName.length() == 0
                    || childName.equals( "." )
                    || childName.equals( ".." )
                    || childName.indexOf( separator) >=0 )
                {
                    ALIB_DBG.WARNING( "Illegal child name {!Q}.", childName );
                    return null;
                }
                return children.get( childName );
            }

            /**
             * Non-checking version of #createChild. Must be used only if it is assured that
             * no child with that name exists, yet.
             *
             * @param childName The name of the child to be created and inserted
             * @return A pointer to the newly created child node.
             */
            public Node createChildNoCheck( String childName )
            {
                Node child= new Node( this ); // create child first, as we are using its name object as key.

                //ALIB_DBG.DEBUG_CODE( auto result= )
                children.put( childName, child );
                //ALIB_DBG.ASSERT_ERROR( result.second, "Internal error. Replacing child node." )
                return child;
            }

            /**
             * Creates and returns a child node. If a node already exists, nothing is done and
             * \c null is returned as this is considered an error.
             *
             * @param  childName The name of the child
             * @param  separator The path separator (used only in debug mode to check file name).
             * @return Pointer to the newly created child in case of success. \c null if a child
             *         with the given name already existed.
             */
            public Node createChild( String childName, char separator )
            {
                ALIB_DBG.ASSERT_ERROR( childName.length() > 0       , "Can note create unnamed node");

                if( getChild( childName, separator ) != null )
                    return null;

                return createChildNoCheck( childName );
            }

            /**
             * Searches and - if no existent - creates a child node.<br>
             * If a child  needs to be created, \p childName  is first checked to not equal
             * to <c>"."</c> or <c>".."</c> and that it does not contain the separation character.
             * If it does, still \c true is returned and with \c null for the new child.
             * Furthermore, an \ref ALIB_DBG.WARNING is reported.
             *
             * @param  childName The name of the child
             * @param  separator The path separator.
             * @param[out] wasCreated Will be set to \c true if the child did not exist and was
              *                       created. To \c false otherwise.
             * @return A pair of the child node found or created and a boolean which is \c true
             *         when the child was created and \c false when it was already existing.
             */
            public Node  getOrCreateChild( String childName, char separator, boolean[] wasCreated )
            {
                Node child= getChild( childName, separator );
                boolean bWasCreated= child==null;
                if( wasCreated != null )
                    wasCreated[0]= bWasCreated;

                if(  bWasCreated )
                {
                    if(    childName.equals( "." )
                        || childName.equals( ".." )
                        || childName.indexOf( separator) >=0 )
                    {
                        ALIB_DBG.WARNING( "Illegal child name {!Q}.", childName );
                    }
                    else
                        child= createChildNoCheck( childName );
                }
                return child;
            }
        };



    // #############################################################################################
    // Constructor/destructor/Clear
    // #############################################################################################
        /** ****************************************************************************************
         * Constructor
         * @param _separator The separator character used by this string tree and inner classes.
         *                   Defaults to <c>'/'</c>.
         ******************************************************************************************/
        public StringTree( char _separator )
        {
            separator = _separator;
            root= new Node( null );
        }


        /** ****************************************************************************************
         * Constructor providing default value \c '/' for paramter \p _separator.
         ******************************************************************************************/
        public StringTree()
        {
            separator = '/';
            root= new Node( null );
        }


        /** ****************************************************************************************
         * Clears all nodes and values.
         ******************************************************************************************/
        public void clear()
        {
            root.children.clear();
            root.value = null ;//default(T);
        }


    // #############################################################################################
    // class Cursor
    // #############################################################################################

        /** ****************************************************************************************
         * This public, inner class provides the main interface into outer class \b StringTree.
         * Only with an object of this class, new nodes can be inserted and removed.
         * As the name indicates, an object of this class represents a current position within
         * a \b %StringTree.
         *
         * The class is very lightweight. In fact, besides a pointer to the \b %StringTree it works
         * on, the only other member  is a pointer to the currently represented node of
         * the \b %StringTree.
         * This allows to copy and move instances of this class very efficiently.
         *
         * For more information on the how this class is used, see
         * \ref java_alib_containers_stringtree_cursor "Inserting, Retrieving And Deleting Nodes".
         ******************************************************************************************/
        public class Cursor
        {

            //####  Protected fields (class Cursor)  #############################################

                /** The node this cursor represents. */
                protected Node                  node;

                /**  A temporary object following the "create once and reuse" design pattern. */
                protected boolean[]             booleanOutputParam;

            //####  Protected methods (class Cursor)  ############################################

                /**
                 * Internal constructor
                 * \note
                 *   Although public, this is an internal constructor. It is public for technical
                 *   reasons, i.e. that inner sibling class
                 *   \ref com.aworx.lib.util.StringTree.Walker "Walker"
                 *   can access it.
                 * @param _node    The node to refer to.
                 */
                protected Cursor(Node _node)
                {
                    node= _node;
                }

                /**
                 * Finds a child node along the \p path given, but does not create new nodes.
                 * Incomplete results may occur if a child along the path was not found.
                 * In this case, parameter \p path contains
                 * the remaining path, excluding a leading separator.
                 *
                 * A leading slash (aka #separator) allows absolute path
                 * addressing, which means the root of \p node is searched if a leading separator
                 * is found.
                 *
                 * Besides normal child names, this method accepts
                 * - multiple separator characters (ignored)
                 * - child name "." (ignored)
                 * - child name ".." for parent node
                 *
                 * If, while processing the path string, the root node is found an the next
                 * path element is "..", this element is ignored and processing continues.
                 * As a sample, the paths:
                 *
                 *      /a/../b
                 * and
                 *
                 *      /a/../../b
                 * both evaluate to
                 *
                 *      /b
                 * assumed that \e /a and \e /b exist.
                 *
                 * @param         node The start node.
                 * @param[in,out] path Creation path. Will be consumed as far as the path exits.
                 * @return The node found
                 */
                protected Node followPath( Node node, Substring path )
                {
                    // check for "root addressing"
                    if( path.charAtStart() == separator )
                    {
                        path.consumeChars( 1 );
                        while( node.parent != null )
                            node= node.parent;
                    }

                    // loop over node names in path
                    for(;;)
                    {
                        // multiple separators are ignored
                        while(path.consumeChar( separator ) )
                            ;

                        if( path.isEmpty() )
                            return node;


                        String name=  path.toString( 0, path.indexOfOrLength( separator ) );


                        if( name.equals( ".." ) )
                        {
                            if( node.parent == null )
                                return node;
                            node= node.parent;
                        }

                        else if( !name.equals( "." ) )
                        {

                            Node nextNode= node.children.get( name );
                            if( nextNode == null )
                                return node;
                            node= nextNode;
                        }

                        path.consumeChars( name.length() );
                    }
                }

                /**
                 * Creates child nodes corresponding to the given \p path.
                 * If the first node already exists, nothing is done and \c null is returned as
                 * this is considered an error.
                 * If the given path is empty the given node is returned as this is \b not
                 * considered an error.
                 *
                 * Child names <c>"."</c> and <c>".."</c> are ignored, but considered an error.
                 * In debug builds, an \ref ALIB_DBG.WARNING is reported.
                 *
                 * The final leaf node is returned.
                 *
                 * @param         node The start node.
                 * @param[in,out] path Creation path. Will be consumed if not errorneous.
                 * @return The leaf node of all created nodes. \c null in the case that the
                 *         first child given in \p path already exists.
                 */
                protected Node createPathAndReturnLeaf( Node node, Substring path )
                {
                    boolean isFirst= true;
                    for(;;)
                    {
                        // consume and check
                        while(path.consumeChar( separator ) )
                            ;
                        if( path.isEmpty() )
                            return node;

                        // get next name
                        String childName= path.toString( 0, path.indexOfOrLength( separator ) );
                        if( childName.equals( "." ) || childName.equals("..") )
                        {
                            ALIB_DBG.WARNING( "Illegal child name {!Q} in creation path", childName );
                            continue;
                        }

                        Node child;
                        if( isFirst )
                        {
                            child= node.createChild( childName, separator );
                            if( child == null )
                                return null;
                        }
                        else
                        {
                            child= node.createChildNoCheck( childName );
                        }
                        isFirst= false;

                        // done?
                        path.consumeChars( childName.length() + 1);
                        node= child;
                    }
                }

            //####  Constructor, comparison operators, etc     #####################################

                /** Public constructor. Creates a cursor which is not valid.   */
                public Cursor()
                {
                    node= root;
                }

                /** Comparison operator.
                 *  @param other  The object to compare ourselves to.
                 *  @return \c true if this and given cursor are equal, \c false otherwise. */
                boolean equals(Cursor other)
                {
                    return node == other.node;
                }

                /**
                 * Return a copy of ourselves.
                 * @return A clone.
                 */
                public Cursor clone()
                {
                    return new Cursor( node );
                }

                /**
                 * Return the \b %StringTree we are working on.
                 * @return The \b %StringTree object.
                 */
                public StringTree<T> getStringTree()
                {
                    return StringTree.this;
                }

                /**
                 * Return the current object.
                 * \note
                 *   Although public, this is an internal method. It is public for technical
                 *   reasons, i.e. that inner sibling class
                 *   \ref com.aworx.lib.util.StringTree.Walker "Walker" can access it.
                 * @return The \b %StringTree object.
                 */
                public Object getNode()
                {
                    return node;
                }

            //####  Tree navigation inplace, returning status      #################################
                /**
                 * Moves this cursor to the root of its \b %StringTree.
                 *
                 * @return this to allow concatenated calls
                 */
                public Cursor   root()
                {
                    node= root;
                    return this;
                }

                /**
                 * Moves this cursor to its parent node.
                 * The method will not move a cursor that is already pointing to the root of the
                 * \b %StringTree into an invalid state.
                 * Instead the cursor remains unchanged and \c false is returned.<br>
                 * The unchecked version #moveToParentUnchecked will turn the cursor into an invalid
                 * state if no parent node exists. This is useful in two situations:
                 * 1. For effective iterating from any node up to
                 *    the \b %StringTree root node. The condition to check in such loop is #isValid.
                 * 2. In situations when it is was already checked that a cursor does not represent
                 *    the root node. This is demonstrated in the following sample taken from this
                 *    classes' method #searchPath:
                 *    \snippet "alib/com/aworx/lib/util/StringTree.java"     DOX_ALIB_STRING_TREE_MOVETOPARENT
                 *
                 * @return \c true if this object was moved to its parent (had a parent), \c false
                 *         otherwise.
                 */
                public boolean    moveToParent()
                {
                    if ( node.parent == null )
                        return false;

                    node= node.parent;
                    return true;
                }

                /**
                 * Non-checking version of #moveToParent.
                 *
                 * @return \c true if this object is valid after the operation, \c false otherwise.
                 */
                public boolean    moveToParentUnchecked()
                {
                    // non-checking version
                    return (node= node.parent) == null;
                }

                /**
                 * Moves this cursor to the child node named \p childName. If no child with this
                 * name exists, the cursor remains as is and \c false is returned.
                 *
                 * This method does not check the given \p childName to to be valid (i.e not equal
                 * to <c>"."</c> or <c>".."</c> or contain a separator character.
                 * Children with this name do not exist and should not be found. However, in
                 * debug compilations, an \ref ALIB_DBG.WARNING is reported.
                 *
                 * @param   childName   The name of the desired child.
                 * @return \c true if the child existed and this object is valid, \c false
                 *         otherwise.
                 */
                public boolean    moveToChild( String childName )
                {
                    // we do not check for illegal names as they will not be found anyhow
                    Node child= node.getChild( childName, separator );
                    if( child == null )
                        return false;
                    node= child;
                    return true;
                }

                /**
                 * Moves this cursor to the child node named \p childName. If no child with this
                 * name exists, one will be created.
                 *
                 * This method checks the given \p childName to not equal to <c>"."</c> or
                 * <c>".."</c> and that it does not contain the separation character.
                 * If it does, \c false is returned and in debug compilations an
                 * \ref ALIB_DBG.WARNING is reported.
                 *
                 * @param  childName The name of the desired child.
                 * @return \c true if the child was found or created, \c false otherwise.
                 */
                public boolean    moveToChildCreate( String childName )
                {
                    if( booleanOutputParam == null )
                        booleanOutputParam =  new boolean[1];
                    Node child= node.getOrCreateChild( childName, separator, booleanOutputParam );
                    if( node == null )
                        return false;
                    node=   child;
                    return  booleanOutputParam[0];
                }

                /**
                 * Moves this cursor along the given path.<br>
                 * The method supports absolute and relative path addressing: If \p path begins
                 * with a separation character, then the cursor is moved to the root of the
                 * \b %StringTree. Furthermore, child name <c>"."</c> is ignored and just skipped while if
                 * <c>".."</c> is found in the path, the cursor is moved to its parent.
                 * Repeated separation characters are ignored.
                 *
                 * If a child along the path does not exist, this cursor remains unchanged and
                 * \c false is returned. This includes the case that child name <c>".."</c> is read
                 * while the cursor references the root node.
                 *
                 * See #moveToExistingPart and #moveToAndCreateNonExistingPart for alternatives.
                 *
                 * @param path      The path to move along.
                 * @return A std.pair of a reference to this cursor and a boolean value.
                 *         The boolean value indicates if the path existed and the move to the node
                 *         specified by \p path was performed.
                 */
                public boolean    moveTo( String path )
                {
                    Substring consumable= new Substring(path);
                    Node dest= followPath( node, consumable );
                    if( consumable.isNotEmpty() )
                        return false;
                    node= dest;
                    return true;
                }

                /**
                 * Moves this cursor along the existing portion of the given path. The method
                 * returns the remaining portion of the path that did not exist.
                 *
                 * See #moveTo and #moveToAndCreateNonExistingPart for alternatives.
                 *
                 * @param path      The path to move along.
                 * @return The unconsumed portion of the path. Empty if the path existed.
                 */
                public Substring   moveToExistingPart( String path )
                {
                    return moveToExistingPart( new Substring( path ) );
                }

                /**
                 * Overloaded version accepting a \b %Substring.
                 *
                 * @param path  The path to move along.
                 * @return The unconsumed portion of the path. Empty if the path existed.
                 *         The object returned is identical to given \p path.
                 */
                public Substring   moveToExistingPart( Substring path )
                {
                    node= followPath( node, path );
                    return path;
                }

                /**
                 * Moves this cursor along the existing portion of the given path and then
                 * creates any non-existing, remaining portion.
                 *
                 * Child names <c>"."</c> and <c>".."</c> in the creation portion of the given path
                 * are ignored, but considered an error.
                 * In debug builds, an \ref ALIB_DBG.WARNING is reported.
                 *
                 * See #moveTo and #moveToExistingPart for alternatives.
                 *
                 * @param path      The path to move along.
                 * @return \c false if the complete path existed, \c true if a part of it was
                 *         created.
                 */
                public boolean    moveToAndCreateNonExistingPart( String path )
                {
                    return moveToAndCreateNonExistingPart( new Substring( path ) );
                }

                /**
                 * Overloaded version accepting a \b %Substring.
                 *
                 * @param path      The path to move along.
                 * @return \c false if the complete path existed, \c true if a part of it was
                 *         created.
                 */
                public boolean    moveToAndCreateNonExistingPart( Substring path )
                {
                    moveToExistingPart( path );
                    if( path.isEmpty() )
                        return false;
                    node= createPathAndReturnLeaf( node, path );
                    return true;
                }

            //####  Node deletion         ##########################################################
                /**
                 * Deletes the children of the node that this cursor refers to.
                 * The cursor itself is not changed.
                 *
                 * @return The number of children that were deleted.
                 */
                public int deleteChildren()
                {
                    int result= node.children.size();
                    node.children.clear();
                    return result;
                }

                /**
                 * Deletes the child named \p childName from the node that this cursor refers to.
                 * The cursor itself is not changed.
                 *
                 * @param   childName   The name of the desired child.
                 * @return \c true if the child existed and was deleted, \c false otherwise.
                 */
                public boolean deleteChild( String childName)
                {
                    return node.children.remove( childName ) != null;
                }

                /**
                 * Deletes the node that this cursor refers to from the tree.
                 * If this cursor did not represent the root node, then after the operation, the
                 * cursor refers to the parent node. Otherwise, only the children are deleted and
                 * the cursor remains representing the same (root) node.
                 *
                 * The method involves a call to #searchName, which - as documented - is not
                 * considered to be efficient. If the name of the current node is known, then
                 * it is advised to use method #deleteChild on the parent of this node.
                 *
                 * @return \c true if this node was not the root node and could be removed from
                 *         the parent. \c false if this not was the root node.
                 */
                public boolean searchNodeNameAndDeleteNode()
                {
                    deleteChildren();
                    if( isRoot() )
                        return false;

                    String name= searchName();
                    node= node.parent;
                    node.children.remove( name );
                    return true;
                }

            //####  node data access interface (Cursor)  #########################################

                /** Retrieves the value of the currently represented node.
                 * @return The current nodes' value.          */
                public T  value()
                {
                    return node.value;
                }

                /**
                 * Sets the given value to the actual node object.
                 * @param value The value to set.
                 */
                public void  setValue( T value)
                {
                    node.value= value;
                }

                /**
                 * Returns the number of direct children.
                 * @return The number of children of the represented node.
                 */
                public int size()
                {
                    return node.children.size();
                }

                /**
                 * Returns the name of the node that this cursor represents.
                 * The method searches all children of this nodes' parent node and returns the
                 * key that this node was stored with. If the represented node is the root
                 * node, \c null is returned.
                 *
                 * \note
                 *   In most situations the name of the node should be available in the context
                 *   where an invocation of this method is considered.
                 *   In other words, this method should be rarely needed and used under the
                 *   presumption that it does not perform in constant execution time.
                 *
                 * @return The name of the represented node.
                 */
                public String searchName()
                {
                    if( node.parent == null )
                        return null;
                    for( Map.Entry<String,Node> sibling : node.parent.children.entrySet() )
                        if( sibling.getValue() == node )
                            return sibling.getKey();
                    ALIB_DBG.ERROR("Internal Error");
                    return null;
                }

               /**
                 * Builds a path string from the root node to this node.
                 * This is done in reverse order, starting from this node using method
                 * #searchName. Hence, this method is <b>not considered efficient</b>!
                 * For each depth-level of the represented node, a 'reverse' search in the parent's
                 * map of children is involved.
                 *
                 * It is recommended to search for other ways to keep track of the current
                 * path of a cursor - outside of this class and use this method for e.g. for debug
                 * purposes or really rare cases.
                 *
                 * @param target        The target to append the path to.
                 * @param targetData    Denotes whether \p target should be cleared prior to
                 *                      appending the path. Defaults to CurrentData.Clear.
                 */
                public void searchPath( AString target, CurrentData targetData )
                {
                    if( targetData == CurrentData.CLEAR )
                        target.clear();

                    if( !isValid() )
                        return;
                    target._( "" ); // set non nulled


                    int insertionPos= target.length();
//! [DOX_ALIB_STRING_TREE_MOVETOPARENT]
Cursor iter= new Cursor( node );
while( !iter.isRoot() )          // <- not root?
{
    if( target.length() > insertionPos )
        target.insertChars( separator, 1, insertionPos );


    target.insertAt( iter.searchName(), insertionPos );

    iter.moveToParentUnchecked();  // <- non-checking version to avoid a redundant check.
}
//! [DOX_ALIB_STRING_TREE_MOVETOPARENT]
                }

               /**
                 * Overloaded version providing default value <c>CurrentData.CLEAR</c> for
                 * paramter \p targetData.
                 *
                 * @param target        The target to append the path to.
                 */
                public void searchPath( AString target )
                {
                    searchPath( target, CurrentData.CLEAR );
                }

                /**
                 * Returns \c true if this cursor represents the root node of the \b %StringTree,
                 * \c false otherwise.
                 * @return \c true if this is the root node, \c false otherwise.
                 */
                public boolean isRoot()
                {
                    return node.isRoot();
                }

                /**
                 * Determines the depth of the node represented by this cursor. This is done by
                 * counting the iterations needed to reach the root node of the tree.
                 * @return The distance from this node to the root node.
                 */
                public int depth()
                {
                    return node.depth();
                }

                /**
                 * Determines if this is a valid cursor. Cursors usually do not get invalid.
                 * See method #moveToParent for more information about how cursors may
                 * get invalid and how this is useful.
                 *
                 * @return \c true if this is a valid cursor. If invalid, \c false is returned and
                 *         the cursor must not be used.
                 */
                public boolean isValid()
                {
                    return node!=null;
                }

                /**
                 * Returns the opposite of #isValid.
                 *
                 * @return \c true if this is an invalid cursor that must not be used, \c false
                 *         otherwise.
                 */
                public boolean isInvalid()
                {
                    return node==null;
                }

        }  // inner class Cursor

        /** ****************************************************************************************
         * Creates a cursor instance representing the root node.
         * @return A cursor pointing to the root node of this \b %StringTree.
         ******************************************************************************************/
        public Cursor  root()
        {
            return new Cursor( root );
        }


        //##########################################################################################
        //  Walker
        //##########################################################################################
        /** ****************************************************************************************
         * This public, inner class implements an iterator that does <b>not</b> apply to the concept
         * of standard Java iterators.
         * The rational for this is the fact that the class provides mechanics to sorting the
         * child nodes, which requires allocation of quite more resources than a usual container
         * iterator. Therefore objects of this type are not supposed to be passed around
         * and copied on the fly. Instead, instances should rather created once and then re-used
         * in subsequent iterations.
         *
         * Sorting of child nodes can be done using a built-in comparison function which works
         * on the child names (path names) and allows to choose ascending and descending order and
         * to ignore letter case, respectively be sensitive about it. Besides this, a custom
         * comparison function for child name based sorting can be established as well as a
         * custom function used to sort by attributes of the custom template type \p T.
         * See methods #sortByPathname and #sortByValue for details on sorting.
         *
         * Objects of this type can initialized, respectively reset to distinct start nodes by
         * providing objects of type
         * - \b %StringTree
         * - \b %StringTree.StdIterator
         * - \b %StringTree.Cursor and
         * - \b %StringTree.Walker
         *
         * to overloaded methods #setStart. Then the iteration is performed with method #next
         * and its end is detected with method #isValid. During iteration, method Skip stops
         * the iteration of the current node and continues with its next sibling.
         *
         * Recursiveness of iteration is controlled with method #setRecursionDepth.
         *
         * Finally, the generation of a string representing the actual path to the current
         * iteration node relative to the start node can be activated. See #pathGeneration
         * for information about this feature.
         *
         * For more information on iterators see description of outer class
         * \ref com.aworx.lib.util.StringTree "StringTree".
         ******************************************************************************************/
        public class Walker
        {
            //######################################################################################
            //  Walker internals (partly public for technical reasons)
            //######################################################################################
                /**
                 * This is a internal, protected helper class implementing the sorting of a list
                 * of child nodes.
                 */
              	public class Sorter implements Comparator<NameAndNode>
                {
                    /** The sort order (used with default path name sorting). */
                    public SortOrder        sortOrder                          = SortOrder.ASCENDING;

                    /** The case comparison rules for built-in path sorting.
                     *  Defaults to <c>StringComparison.CurrentCultureIgnoreCase.</c>             */
                    public Case             sensitivity                               = Case.IGNORE;

                    /** A user-defined comparison method for path names. */
                    public Comparator<String> pathSorter                                     = null;

                    /** A user-defined comparison method for sorting by value types. */
                    public Comparator<T>      valueSorter                                    = null;

                    /**
                     * This is the compare function, which will be invoked by \c Colletions.sort.
                     * @param lhs   The left hand side operand.
                     * @param rhs   The right hand side operand.
                     * @return The 'difference' between the given names or nodes.
                     */
                    @Override
                    public int compare( NameAndNode lhs, NameAndNode rhs )
                    {
                        if( pathSorter != null )
                            return pathSorter.compare( lhs.name, rhs.name );

                        if( valueSorter != null )
                            return valueSorter.compare( lhs.node.value, rhs.node.value );


                        return    ( sortOrder == SortOrder.ASCENDING  ? 1 : -1 )
                                * (  sensitivity == Case.SENSITIVE ?  lhs.name.compareTo          ( rhs.name )
                                                                   :  lhs.name.compareToIgnoreCase( rhs.name ) );
                    }
                }

                /** Internal class used to store the data of recursive iterations. */
                protected class NameAndNode
                {
                    /** The name of the node. */
                    public String                  name;

                    /** The node */
                    public Node                    node;

                    /**
                     * Constructor.
                     * @param _name The name of the node
                     * @param _node The node
                     */
                    public NameAndNode(String _name, Node _node)
                    {
                        name= _name;
                        node= _node;
                    }
                }

                /** Protected, internal class used to store the data of recursive iterations. */
                protected class RecursionData
                {
                    /** The current node */
                    public Node                                 node;

                    /** The name of the current node. */
                    public String                               nodeName;

                    /** A vector of children copied from the map to this vector for the purpose of
                     *  sorting them. */
                    public ArrayList<NameAndNode>               sortedChildren;

                    /** The current child of the current node in case of sorted access
                     *  If this is pointing to the end of the child map, then
                     *  the actual node itself is selected by this walker. */
                    public int                                  actChild;

                    /**
                     * Reset to point to the given node. Used in each recursion step.
                     * Copies all children from the map to a vector and sorts them there.
                     * @param _node     The node to store.
                     * @param _nodeName The name of the node to store.
                     * @param _sorter   The sorter used to sort the children in the node.
                     */
                    public void reset( Node _node, String _nodeName, Sorter _sorter )
                    {
                        node=     _node;
                        nodeName= _nodeName;
                        if( sortedChildren == null )
                            sortedChildren= new ArrayList<NameAndNode>();
                        else
                            sortedChildren.clear();

                        sortedChildren.ensureCapacity( node.children.size() );

                        for( Map.Entry<String,Node> child: node.children.entrySet() )
                            sortedChildren.add( new NameAndNode( child.getKey(), child.getValue() ) );

                        Collections.sort( sortedChildren, _sorter );

                        actChild= -1;
                    }
                }

                /** A stack holding the recursive list of child maps and the  idx of their current
                 * child. Implemented as a vector in combination with member #stackSize, to reuse
                 * allocated storage space.  */
                protected ArrayList<RecursionData>   stack         = new ArrayList<RecursionData>();

                /** The current use of the stack. */
                protected int                   stackSize                                       = 0;

                /** The path to the actual node (excluding the name of the actual node). */
                protected AString               actPath                             = new AString();

                /** The sorter object. This is a fixed member of the parent class providing a method
                 *  to sort children by name or value type \p T.*/
                protected Sorter                sorter                               = new Sorter();

                /** The requested depth of iteration recursion. */
                protected int                   recursionDepth                  = Integer.MAX_VALUE;

                /**
                 * Internal method to identify the actual node.
                 * @return Pointer to the node object that we currently represent.
                 */
                protected Node actNode()
                {
                    ALIB_DBG.ASSERT_ERROR(isValid(), "Invalid walker");

                    RecursionData  nc= stack.get( stackSize -1 );
                    return         nc.actChild < 0 ?  nc.node
                                                   :  nc.sortedChildren.get(nc.actChild).node;
                }

                /**
                 * Resets this walker to represent to the given node.
                 *
                 * @param newNode           The new node to start from
                 */
                protected void setStart( StringTree<T>.Node newNode )
                {
                    actPath.clear();

                    stackSize= 1;
                    if( newNode == null )
                        newNode= stack.get(0).node;
                    stack.get(0).reset(newNode, "", sorter  );

                    // skip root node if recursion depth is limited
                    if( recursionDepth != Integer.MAX_VALUE )
                        next();
                }

            //######################################################################################
            //  Walker public interface
            //######################################################################################
                /**
                 * Constructor
                 */
                public Walker()
                {
                    RecursionData stack0= new RecursionData();
                    stack0.sortedChildren= new ArrayList<NameAndNode>();
                    stack.add( stack0 );
                    setStart( root );
                }

                /**
                 * Return the \b %StringTree we are working on.
                 * @return The \b %StringTree object.
                 */
                public StringTree<T> getStringTree()
                {
                    return StringTree.this;
                }

                /**
                 * Resets this walker to work with the root node of its outer \b %StringTree.
                 */
                public void setStart()
                {
                    setStart( root );
                }

                /**
                 * Resets this %walker to represent the node that the given cursor object represents.
                 * @param cursor  The cursor to copy the represented node from.
                 */
                public void setStart( Cursor cursor )
                {
                    ALIB_DBG.ASSERT_ERROR( StringTree.this == cursor.getStringTree(), "Differnt referred StringTree objects" );
                    setStart( (Node) cursor.getNode() );
                }

                /**
                 * Resets this walker to represent the same node that the given other walker
                 * object represents.
                 * @param other  The walker to copy the represented node from.
                 */
                public void setStart( Walker other )
                {
                    ALIB_DBG.ASSERT_ERROR( StringTree.this == other.getStringTree(), "Differnt referred StringTree objects" );
                    setStart( other.actNode() );
                }

                /**
                 * Invalidates this object. After invoking this method, this walker can not be
                 * used further, until #setStart is invoked.
                 * After the invocation, method #isValid will return \c false.
                 */
                public void invalidate()
                {
                    stackSize= 0;
                }

                /**
                 * Determines if this is a valid walker. Walkers may become invalid after
                 * invocations of method #next at the end of the iteration and become valid with
                 * the invocation of one of the overloaded methods #setStart
                 * (when invoked with valid objects).
                 *
                 * @return \c true if this is a valid cursor. If invalid, \c false is returned and
                 *         the cursor must not be used.
                 */
                public boolean isValid()
                {
                    return stackSize != 0;
                }

                /**
                 * Returns the opposite of #isValid.
                 *
                 * @return \c true if this is an invalid cursor that must not be used, \c false
                 *         otherwise.
                 */
                public boolean isInvalid()
                {
                    return stackSize == 0;
                }

                /**
                 * Sets the sorting of children by their path name, using the built-in comparison
                 * method, which in turn uses C# method <b>String.Compare</b>.
                 *
                 * Overloaded methods, which allow different sorting mechanics exist.
                 * This method should be invoked prior to the invocation of one of the #setStart
                 * methods which start the iteration. Invocation during iteration is allowed,
                 * but only nodes that have not been visited yet will be affected by the new
                 * sorting.
                 *
                 * @param order         The sort order.
                 * @param sensitivity   Denotes whether sorting is case sensitive or not.
                 *                      Defaults to \b %Case.IGNORE.
                 */
                public void sortByPathname( SortOrder order, Case sensitivity )
                {
                    sorter.sortOrder=       order;
                    sorter.sensitivity=     sensitivity;
                    sorter.valueSorter=     null;
                    sorter.pathSorter=      null;
                }

                /**
                 * Overloaded version providing default value \c Case.IGNORE for parameter
                 * \p sensitivity.
                 *
                 * @param order         The sort order.
                 *                      Defaults to \b %SortOrder.Ascending.
                 */
                public void sortByPathname( SortOrder  order )
                {
                    sortByPathname( order, Case.IGNORE );
                }

                /**
                 * Sets the sorting of children by their path name, using the given delegate.
                 *
                 * Overloaded methods, which allow different sorting mechanics exist.
                 * This method should be invoked prior to the invocation of one of the #setStart
                 * methods which start the iteration. Invocation during iteration is allowed,
                 * but only nodes that have not been visited yet will be affected by the new
                 * sorting.
                 *
                 * @param pathSorter    A custom comparison method used for sorting the children
                 *                      of the nodes.
                 */
                public void sortByPathname( Comparator<String> pathSorter )
                {
                    sorter.valueSorter= null;
                    sorter.pathSorter=  pathSorter;
                }

                /**
                 * Sets the sorting of children by their template value, using the given delegate.
                 *
                 * Overloaded methods, which allow different sorting mechanics exist.
                 * This method should be invoked prior to the invocation of one of the #setStart
                 * methods which start the iteration. Invocation during iteration is allowed,
                 * but only nodes that have not been visited yet will be affected by the new
                 * sorting.
                 *
                 * @param valueSorter  A custom comparison method used for sorting the children
                 *                     of the nodes.
                 */
                public void sortByValue( Comparator<T> valueSorter )
                {
                    sorter.valueSorter= valueSorter;
                    sorter.pathSorter=  null;
                }

                /**
                 * Sets the requested recursion dept. A value of \c 0 or negative sets unlimited
                 * recursion depth.<br>
                 * Please note the explanation of recursion depth parameter in section
                 * \ref java_alib_containers_stringtree_iterator "Recursive Iteration"
                 * of the parent class description.
                 *
                 * @param _recursionDepth Sets the new recursion dept.
                 *                        Use \c 0 for unlimited recursion.
                 */
                public void setRecursionDepth( int _recursionDepth )
                {
                    recursionDepth= _recursionDepth <= 0 ? Integer.MAX_VALUE : _recursionDepth;
                }

                /**
                 * With this method, the generation of the actual path string is activated. The
                 * given character is used as separation character. The current path can
                 * be received using method #getPath.<br>
                 * The method must be invoked prior to start walking with method #next, otherwise
                 * undefined behavior might occur while 'walking'.
                 *
                 * @param generatePath Denotes whether the path should be generated or not.
                 */
                public void pathGeneration( Switch generatePath )
                {
                    if( generatePath == Switch.ON )
                        actPath._( "" ); // set non-nulled
                    else
                        actPath.setNull();
                }

                /** Retrieves the current StringTree nodes value.
                 * @return The current StringTree node templated, custom value.    */
                public T value()
                {
                    return actNode().value;
                }

                /**
                 * Sets the given value to the actual node object.
                 * @param value The value to set.
                 */
                public void  setValue( T value )
                {
                    actNode().value= value;
                }

                /**
                 * Skips remaining children of the current node and continues with its next
                 * sibling.
                 */
                public void skip()
                {
                    ALIB_DBG.ASSERT_ERROR( isValid(), "Invalid iterator");
                    RecursionData nc= stack.get( stackSize - 1 );
                    if( nc.sortedChildren.size() > 0 )
                        nc.actChild= nc.sortedChildren.size() - 1;

                    next();
                }

                /**
                 * Goes to the next node.
                 *  @return The result of #isValid after the 'walk'. */
                public boolean next()
                {
                    ALIB_DBG.ASSERT_ERROR( isValid(), "Invalid iterator");
                    while( stackSize > 0 )
                    {
                        RecursionData nc= stack.get( stackSize - 1 );

                        if( nc.actChild < 0 )
                            nc.actChild=   0;
                        else
                            nc.actChild++;

                        // not end of child ?
                        if( nc.actChild < nc.sortedChildren.size() )
                        {
                            // set path string (if activated)
                            if( stackSize < recursionDepth )
                            {
                                // set path string for #GetPath
                                if( stackSize > 1 && actPath.isNotNull() )
                                {
                                    if( actPath.length() > 0 )
                                        actPath._( separator );
                                    actPath._( nc.nodeName );
                                }

                                if( stack.size() == stackSize )
                                    stack.add( new RecursionData() );

                                stack.get( stackSize ).reset( nc.sortedChildren.get( nc.actChild ).node,
                                                              nc.sortedChildren.get( nc.actChild ).name, sorter );
                                stackSize++;
                            }
                            break;
                        }

                        // climb down
                        stackSize--;
                        if( stackSize > 1 && actPath.isNotNull() )
                        {
                            actPath.deleteEnd( stack.get( stackSize - 1 ).nodeName.length() );
                            if ( actPath.charAtEnd() == separator )
                                actPath.deleteEnd( 1 );
                        }
                    }

                   return isValid();
                }

                /**
                 * Retrieves the current path of walking as a string representation.
                 * The path returned is relative to the start node and does not contain a leading
                 * separator character. Also, it does not contain the name of the current node,
                 * which can be received with method #name.
                 *
                 * Note that this method can be used only if path generation was activated
                 * prior to the current iteration. Activation is performed with method
                 * #pathGeneration.
                 *
                 * Note, that the AString returned must not be modified by the receiver.
                 *
                 * @return The path of the current node.
                 */
                public AString    getPathToNode()
                {
                    ALIB_DBG.ASSERT_ERROR( actPath.isNotNull() , "Path generation not activated" );
                    return actPath;
                }

                /**
                 * Writes the results of  #getPathToNode and #name, separated by a separator char.
                 *
                 * Note that this method can be used only if path generation was activated
                 * prior to the current iteration. Activation is performed with method
                 * #pathGeneration.
                 *
                 * @param target        The target to append the path to.
                 * @param targetData    Denotes whether \p target should be cleared prior to
                 *                      appending the path. Defaults to CurrentData.Clear.
                 * @return The given string to allow concatenated operations
                 */
                public AString     getPath( AString target, CurrentData targetData )
                {
                    ALIB_DBG.ASSERT_ERROR( actPath.isNotNull() , "Path generation not activated" );

                    if( targetData == CurrentData.CLEAR )
                        target.clear();

                    if( actPath.isNotEmpty() )
                        target._( actPath )._( separator );

                    return target._( name() );
                }

                /**
                 * Overloaded version providing default value <c>CurrentData.CLEAR</c> for
                 * paramter \p targetData.
                 *
                 * @param target        The target to append the path to.
                 * @return The given string to allow concatenated operations
                 */
                public AString     getPath( AString target )
                {
                    return getPath( target, CurrentData.CLEAR );
                }

                /**
                 * Returns the name of the node that this walker currently represents.
                 * The name of the node corresponds to the path segment or child name that was
                 * used to create it.
                 *
                 * \note Unlike method
                 *       \ref com.aworx.lib.util.StringTree.Cursor.searchName "Cursor.searchName"
                 *       which needs some effort to search the name of a node represented by a
                 *       cursor, this method performs in constant time, as the current child name
                 *       is made available during iteration.
                 *
                 * @return The name of the represented node.
                 */
                public String name()
                {
                    ALIB_DBG.ASSERT_ERROR( isValid(), "Invalid iterator");

                    RecursionData nc= stack.get( stackSize - 1 );
                    return     nc.actChild < 0 ?  nc.nodeName
                                               :  nc.sortedChildren.get(nc.actChild).name;
                }

                /**
                 * Returns the  number of direct children of the currently represented node.
                 * @return The number of children of the represented node.
                 */
                public int size()
                {
                    return actNode().children.size();
                }

                /**
                 * Returns the depth of the current iteration. This is value is available to the
                 * algorithm which means this method executes in constant time.
                 *
                 * To get the absolute depth of the current node, use a combination of method
                 * #getCursor and
                 * \ref com.aworx.lib.util.StringTree.Cursor.depth "Cursor.depth".
                 *
                 * @return The distance of the current node and the node of the start of the
                 *         iteration.
                 */
                public int depth()
                {
                    return stackSize - 1;
                }

                /**
                 * Creates a cursor referencing the same node that this walker references.
                 * @return A cursor object referencing the current node.
                 */
                public Cursor getCursor()
                {
                    return new Cursor( actNode() );
                }

        }  // inner class "Walker"

} // class StringTree
