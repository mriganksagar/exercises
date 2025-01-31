package homegrownDatastructures

// A representation of Tree and specific type of trees using inhertence and OOP
// My own implementation , (might have some issues too)

sealed trait Tree[+T]{
    // common tree methods
}

sealed trait PositionedTree[+T] extends Tree[T] {
    // methods specific to PositionedTree
}
sealed trait BoundedTree[+T] extends Tree[T] {
    // methods specific to BoundedTree
}

case class Node[+T](
    value: T,
    left: Tree[T] = EndNode,
    right: Tree[T] = EndNode
) extends Tree[T] {
    // methods common for node
}

object EndNode extends Tree[Nothing] with PositionedTree[Nothing] with BoundedTree[Nothing]{
    // all methods for all types of endnodes
    // by making it Tree[Nothing, Nothing] i can use this EndNodee for all treeType
}

class PositionedNode[+T](
    v: T,
    l: Tree[T],
    r: Tree[T],
    val x: Int,
    val y: Int
) extends Node(v, l, r)
    with PositionedTree[T]

class BoundedNode[+T](
    v: T,
    l: Tree[T],
    r: Tree[T],
    val bounds: List[(Int, Int)]
) extends Node(v, l, r)
    with BoundedTree[T]

object deemo extends App {
    val v = PositionedNode(4, PositionedNode(1, EndNode, EndNode, 0,0), EndNode, 1,1)

    println(v.getClass())
    println(v.isInstanceOf[PositionedTree[Int]])
    println(v.isInstanceOf[Node[Int]])
    println(EndNode.isInstanceOf[PositionedTree[Int]])
    println(EndNode.isInstanceOf[Tree[Int]])
}