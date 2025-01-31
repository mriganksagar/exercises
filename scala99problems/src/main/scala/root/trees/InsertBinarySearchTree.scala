package root.trees

import root.{Tree, Node, EndNode}
//Write a function to add an element to a binary search tree.

object BinarySearchTree {

    // p57  create an insert method for binary search tree
    // I am creating it as an extension method to make usage easier

    /*  
        Instead of extending over Tree[T] and pattern match for sub types
        I can create multiple extension methods for different sub types

        I think:
        first method seems simpler but in some cases when more subtypes are created
        it needs change in a possibly huge method, second method demonstrate separating concerns
    
    extension [T: Ordering](root: Tree[T])
        def insert(e: T): Tree[T] = root match
            case EndNode => Node(e)
            case Node(value, leftSubtree, rightSubtree) =>
                if summon[Ordering[T]].lt(e, value) then
                    Node(value, leftSubtree.insert(e), rightSubtree)
                else Node(value, leftSubtree, rightSubtree.insert(e))

    */

    extension [T: Ordering] (root: Tree[T])
        def insert(e: T): Tree[T] = root match
            case EndNode => EndNode.insert(e)
            case root: Node[T] => root.insert(e)

    extension [T](root: Node[T])(using ord: Ordering[T])
        def insert(e: T): Node[T] = {
            if ord.lt(e, root.value) then
                Node(root.value, root.left.insert(e), root.right)
            else Node(root.value, root.left, root.right.insert(e))
        }

    extension (endNode: EndNode.type) def insert[T](e: T): Node[T] = Node(e)

}

object DemoProblems extends App {
    import BinarySearchTree._
    val bst1 = Node(60)
        .insert(43)
        .insert(12)
        .insert(30)
        .insert(89)
        .insert(77)
        .insert(12)
        .insert(15)
        .insert(99)
    val bst2 = Node(1).insert(2)
    println(bst2)
    println(bst1)
}
