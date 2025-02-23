package homegrownDatastructures

// A representation of Tree and specific type of trees using inhertence and OOP
// My own implementation , (might have some issues too)

sealed trait Tree[+T] {
    // common tree methods
}

sealed trait PositionedTree[+T] extends Tree[T] {
    // methods specific to PositionedTree
}

sealed trait BoundedTree[+T](val bounds: List[(Int, Int)]) extends Tree[T] {
    // methods specific to BoundedTree
}

// case class Node[+T](
//     value: T,
//     left: Tree[T] = EndNode,
//     right: Tree[T] = EndNode
// ) extends Tree[T] {
//     // methods common for node
// }

/* 
    creating it so that left of positioned node can be positioned node instead of just node
    however i had to remove +T covariant because of extending it in PositionedNode and bounding node
    it was giving error that it appears in contravariant position i.e when Node instantiation 
 */

case class Node[U <: Tree, T](
    value: T,
    left: U[T] = EndNode,
    right: U[T] = EndNode
) extends Tree[T] {
    // common methods
}

sealed trait EndNode extends Tree[Nothing] {
    // all common methods
}

case object EndNode extends EndNode

class PositionedNode[T](
    v: T,
    l: PositionedTree[T],
    r: PositionedTree[T],
    val x: Int,
    val y: Int
) extends Node(v, l, r)
    with PositionedTree[T] {
    override def toString(): String =
        s"PN(${super.toString()}, x is ${this.x} and y is ${this.y}})"
}

object PositionedNode {
    def unapply[T](v: PositionedNode[T]) =
        Some(Node(v.value, v.left, v.right), v.x, v.y)
}

case object PositionedEnd extends EndNode with PositionedTree[Nothing] {
    // methods for positionedEnd
    override def toString() = "[PE]"
}

class BoundedNode[T](
    v: T,
    l: BoundedTree[T],
    r: BoundedTree[T],
    bounds: List[(Int, Int)],
    val edgeLength: Int
) extends Node(v, l, r)
    with BoundedTree[T](bounds)

object BoundedNode {
    def unapply[T](v: BoundedNode[T]) =
        Some(v.value, v.left, v.right, v.bounds, v.edgeLength)
}

case object BoundedEnd extends EndNode with BoundedTree[Nothing](Nil) {
    // methods for boundedEnd
}

object deemo extends App {
    val v = PositionedNode(
      4,
      PositionedNode(1, PositionedEnd, PositionedEnd, 0, 0),
      PositionedEnd,
      1,
      1
    )

    println(v.getClass())
    println(v.isInstanceOf[PositionedTree[Int]]) // true
    println(v.isInstanceOf[Node[Tree, Int]])    // true
    println(EndNode.isInstanceOf[Tree[Int]])   // true

    val x: Tree[Int] = Node(1, EndNode, EndNode)


    // exhaustive matching works well in case of simple Simple Trees
    x match
        case Node(value, left, right) => println("it is a node")
        case e: EndNode               => println("endnode")

    // pattern matching unapply works well
    v match
        case PositionedNode(Node(value, left, right), x, y) =>
            println(s" $left, $right")
}
