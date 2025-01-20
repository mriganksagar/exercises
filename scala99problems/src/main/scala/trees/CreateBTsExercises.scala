/*
    P55 (**) Construct completely balanced binary trees.
    this is an exercise to create a balanced binary tree given the number of nodes
    give all possible solutions
 */

object CreateBTsExercises {
    def completelyBalancedBTs[T](v: T)(n: Int): List[Tree[T]] = {
        if n == 0 then List(EndNode)
        else {
            if n % 2 == 1 then {
                val subTrees = completelyBalancedBTs(v)(n / 2)
                for {
                    subTree1 <- subTrees
                    subTree2 <- subTrees
                } yield Node(v, subTree1, subTree2)
            } else
                for {
                    subTree1 <- completelyBalancedBTs(v)(n / 2)
                    subTree2 <- completelyBalancedBTs(v)(n / 2 - 1)
                    combinedTree <- List(
                      Node(v, subTree1, subTree2),
                      Node(v, subTree2, subTree1)
                    )
                } yield combinedTree
        }
    }

    import ShapeBTsExercises._
    def symmetricCompletelyBalancedBTs[T](v: T)(n: Int): List[Tree[T]] = 
        completelyBalancedBTs(v)(n).filter(isMirroredStructure)
    
}
object P55Demo extends App {
    println(CreateBTsExercises.completelyBalancedBTs("x")(4))
}
