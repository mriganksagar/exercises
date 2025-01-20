/*
    P56 (**) Symmetric binary trees.
    symmetric if you can draw a vertical line through the root node and then the right subtree is the mirror image of the left subtree.
 */

// writing a method to check whether two tree have same structure or not. ignoring values

object shapeBTsExercises {
  def haveSameStructure[T](a: Tree[T], b: Tree[T]): Boolean = (a, b) match {
    case (Node(_, tree1left, tree1right), Node(_, tree2left, tree2right)) =>
      haveSameStructure(tree1left, tree2left) && haveSameStructure(
        tree1right,
        tree2right
      )
    case (EndNode, EndNode) => true
    case _                  => false
  }
  
  def haveMirrorStructure[T](a: Tree[T], b: Tree[T]): Boolean = (a, b) match {
    case (Node(_, tree1left, tree1right), Node(_, tree2left, tree2right)) =>
      haveMirrorStructure(tree1left, tree2right) && haveMirrorStructure(
        tree1right,
        tree2left
      )
    case (EndNode, EndNode) => true
    case _                  => false
  }
  
  def isMirroredStructure[T](a: Tree[T]): Boolean = haveMirrorStructure(a, a)  
}

object P66Demo extends App {

  // val t1 = Node(0, Node(1), Node(2))
  // val t2 = Node(10, Node(2), Node(33))

  val t3 = Node(0, Node(1, Node(2, EndNode, Node(3)), EndNode), EndNode)
  // val t4 = Node(0, EndNode, Node(1, Node(2, EndNode, Node(3)), EndNode))
  val t5 = Node(0, EndNode, Node(1, EndNode, Node(2, Node(3), EndNode)))

  // println(haveSameStructure(t1, t2))

  // println(haveMirrorStructure(t1, t2))

  println(shapeBTsExercises.haveMirrorStructure(t3, t5))
  // println(t3.toString())
  // println(t5.toString())
  // println(haveMirrorStructure(t3, t3))

  val aMirroredTree = Node(
    0,
    Node(
      1,
      left = Node(
        2,
        right = Node(3, right = Node(4, left = Node(5, Node(6), Node(7))))
      )
    ),
    Node(
      8,
      right = Node(
        9,
        left = Node(10, left = Node(11, right = Node(12, Node(13), Node(14))))
      )
    )
  )

  println(shapeBTsExercises.isMirroredStructure(aMirroredTree)) // prints true
}
