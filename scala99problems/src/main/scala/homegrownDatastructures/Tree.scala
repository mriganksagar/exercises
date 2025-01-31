package homegrownDatastructures



sealed trait TreeType
object TreeType {
    trait Positioned extends TreeType
    trait Bounded extends TreeType
}

sealed trait Tree[+T, +X <: TreeType]

sealed trait PositionedTree[+T] extends Tree[T, TreeType.Positioned] {
    // methods specific to PositionedTree
}
sealed trait BoundedTree[+T] extends Tree[T, TreeType.Bounded] {
    // methods specific to BoundedTree
}

case class Node[+T, +X <: TreeType](
    value: T,
    left: Tree[T, X] = EndNode,
    right: Tree[T, X] = EndNode
) extends Tree[T, X] {
    // methods common for node
}

case object EndNode extends Tree[Nothing, Nothing] {
    // all methods for all types of endnodes
    // by making it Tree[Nothing, Nothing] i can use this EndNodee for all treeType
}


class PositionedNode[+T](
    v: T,
    l: Tree[T, TreeType.Positioned],
    r: Tree[T, TreeType.Positioned],
    val x: Int,
    val y: Int
) extends Node(v, l, r)
    with PositionedTree[T]


class BoundedNode[+T](
    v: T,
    l: Tree[T, TreeType.Bounded],
    r: Tree[T, TreeType.Bounded],
    val bounds: List[(Int, Int)]
) extends Node(v, l, r)
    with BoundedTree[T]


/* 
    Using this structure
    I can represent subtypes of trees 
 */