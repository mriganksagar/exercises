package root.trees

import root.{Tree, Node, EndNode}

object TreeOps {
    /*
            P61: count leaves of a Binary tree
            P61-A : collect leaves of a binary tree into a list
     */
    def countNodes[T](root: Tree[T]): Int = root match
        case EndNode => 0
        case Node(_, leftSt, rightSt) => 1 + countNodes(leftSt) + countNodes(rightSt)

    def countLeaf[T](root: Tree[T]): Int = root match
        case EndNode                   => 0
        case Node(_, EndNode, EndNode) => 1
        case Node(_, left, right)      => countLeaf(left) + countLeaf(right)

    def collectLeaves[T](root: Tree[T]): List[T] = root match
        case EndNode                       => Nil
        case n @ Node(v, EndNode, EndNode) => List(v)
        case Node(_, left, right) => collectLeaves(left) ++ collectLeaves(right)

    /*
            P62 collect internal nodes of a binary tree in a list
            P62B collect nodes at a given level
     */

    def collectInternalNodes[T](root: Tree[T]): List[T] = root match
        case EndNode                   => Nil
        case Node(_, EndNode, EndNode) => Nil
        case Node(v, left, right) =>
            v :: collectInternalNodes(left) ::: collectInternalNodes(right)

    def collectNodesAtLevel[T](root: Tree[T], level: Int): List[T] =
        (level, root) match
            case (l, Node(v, left, right)) =>
                if l <= 0 then Nil
                else if l == 1 then List(v)
                else
                    collectNodesAtLevel(left, l - 1) ::: collectNodesAtLevel(
                      right,
                      l - 1
                    )
            case (_, EndNode) => Nil
}
