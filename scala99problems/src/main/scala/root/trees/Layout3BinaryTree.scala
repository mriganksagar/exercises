package root.trees

import homegrownDatastructures.*

/*
 P66 (***) Layout a binary tree (3).
 pack the layout tightly but with sufficient space between nodes in same level

 soln: 
    I need to know how much horizonal span left and right subtree takes
    and need to distance required between those subtrees, after that i can know
    how much should be the edge length for the root that will add those left right subtrees
    then find x-offset for the root and recursively give subtrees their position based on 
    edge length of root
 */

def createBoundedTree[T](root: Tree[T]): BoundedTree[T] = root match
    case Node(value, left, right) => {
        val leftBT = createBoundedTree(left)
        val rightBT = createBoundedTree(right)
        // it is the needed horizontal distance between left and right subtrees
        val edgeL = leftBT.bounds.view
            .zip(rightBT.bounds)
            .map((a, b) => a._2 - b._1 + 1)
            .maxOption
            .map {
                case n if n % 2 == 1 => (n + 1) / 2
                case n               => n / 2
            }
            .getOrElse(1)

        val rootBounds = (0,0) :: leftBT.bounds.view
            .map((a, b) => Some(a - edgeL, b - edgeL))
            .zipAll(
              rightBT.bounds.map((a, b) => Some(a + edgeL, b + edgeL)),
              None,
              None
            )
            .collect {
                case (Some(l1, l2), Some(r1, r2)) => (l1, r2)
                case (None, Some(r))              => r
                case (Some(l), None)              => l
            }.toList
        
        BoundedNode(value, leftBT, rightBT, rootBounds, edgeL)
    }
    case _: EndNode => BoundedEnd


def layout3aux[T](root:BoundedTree[T], y: Int, x: Int): PositionedTree[T] = root match
    case BoundedNode[T](v, l, r, b, e) => PositionedNode(v, layout3aux(l, y+1, x-e), layout3aux(r, y+1, x+e), x, y)
    case BoundedEnd => PositionedEnd

def layout3[T](root: Tree[T]): PositionedTree[T] = {
    val boundedTree = createBoundedTree(root)
    val rootXoffset = boundedTree.bounds.map(-_._1).max

    layout3aux(boundedTree, 0, rootXoffset)
}

object Layout3Demo extends App {
    val result = layout3(Node('a', Node('b', EndNode, Node('c')), Node('d')))
    println(result.toString())
}
