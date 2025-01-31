package root.trees

import root.{Tree, Node, EndNode}

class PositionedNode[T](v: T, l: Tree[T], r: Tree[T], val x: Int, val y: Int)
    extends Node(v, l, r)

object LayoutBinaryTree {

    /*
        P64 layout binary tree
        x axis value is inorder sequence
        y axis is depth of the node
     */

    def layout[T](root: Tree[T]): Tree[T] = {
        def auxLayout(root: Tree[T], raw_x: Int, y: Int): (Int, Tree[T]) =
            root match
                case EndNode => (raw_x, EndNode)
                case Node(v, l, r) => {
                    val (x, leftSt) = auxLayout(l, raw_x, y + 1)
                    val (x_new, rightSt) = auxLayout(r, x + 1, y + 1)
                    x_new -> PositionedNode(v, leftSt, rightSt, x, y)
                }
        auxLayout(root, 1, 1)._2
    }

    /*
        Layout a binary tree (2nd)

        the edge to the bottom most level goes from x to x+1
        the edge from third to second bottom level is length 2 horizontally
        and so on , 4, 8, and it grows exponentially

        but as the x of root is dependent on subtrees
        we first figure out x of root and then it is easy to tell its subtrees their x axis

     */

    def layout_2[T](root: Tree[T]): Tree[T] = {
        val totalDepth = root.maxDepth
        val leftMostDepth = root.leftMostDepth

        def auxLayout(root: Tree[T], x: Int, y: Int): Tree[T] = root match
            case EndNode => EndNode
            case Node(value, left, right) => {
                val edgeWidth = Math.pow(2, totalDepth - y).toInt
                PositionedNode(
                  value,
                  auxLayout(left, x - edgeWidth, y + 1),
                  auxLayout(right, x + edgeWidth, y + 1),
                  x,
                  y
                )
            }

        val x_of_root = (2 to leftMostDepth)
            .map((n) => Math.pow(2, totalDepth - n).toInt)
            .reduceLeft(_ + _) + 1
        auxLayout(root, x_of_root, 1)
    }

}
