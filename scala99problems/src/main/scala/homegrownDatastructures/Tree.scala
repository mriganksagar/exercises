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
    left: Tree[T] = End,
    right: Tree[T] = End
) extends Tree[T] {
    // methods common for node
}

case object End extends EndNode

sealed trait EndNode extends Tree[Nothing] {
    // all common methods
}

class PositionedNode[+T](
    v: T,
    l: PositionedTree[T],
    r: PositionedTree[T],
    val x: Int,
    val y: Int
) extends Node(v, l, r)
    with PositionedTree[T]

object PositionedNode{
    def unapply[T](v: PositionedNode[T]) =
        Some(Node(v.value, v.left, v.right), v.x, v.y)
}

case object PositionedEnd extends EndNode with PositionedTree[Nothing] {
    // methods for positionedEnd
}

class BoundedNode[+T](
    v: T,
    l: BoundedTree[T],
    r: BoundedTree[T],
    val bounds: List[(Int, Int)]
) extends Node(v, l, r)
    with BoundedTree[T]

case object BoundedEnd extends EndNode with BoundedTree[Nothing]{
    // methods for boundedEnd
}

object deemo extends App {
    val v = PositionedNode(4, PositionedNode(1, PositionedEnd, PositionedEnd, 0,0), PositionedEnd, 1,1)

    println(v.getClass())
    println(v.isInstanceOf[PositionedTree[Int]])
    println(v.isInstanceOf[Node[Int]])
    println(End.isInstanceOf[Tree[Int]])

    val x : Tree[Int] = Node(1, End, End)

    x match
        case Node(value, left, right) => println("it is a node")
        case e:EndNode => println("endnode")

    
    v match
        case PositionedNode(Node(value, left, right), x, y) => println(s" $left,;;; $right")
    
}