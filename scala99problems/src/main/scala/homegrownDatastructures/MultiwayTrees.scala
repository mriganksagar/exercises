package homegrownDatastructures

// P70 (**) Tree construction from a node string
case class MTree[+T](value: T, children: List[MTree[T]] = Nil){
    override def toString(): String = s"$value {${children.mkString(",")}}"

    def countNodes: Int = 1 + children.map(_.countNodes).sum
}

object MTree{
    private def createMTreeAux(s: String): (MTree[Char], String) = {
        def mSubtrees(s: String): (List[MTree[Char]], String) = {
            if s(0) == '^' then Nil -> s.drop(1)
            else {
                val (firstChild, restString) = createMTreeAux(s)
                val rest = mSubtrees(restString)
                (firstChild:: rest._1) -> rest._2 
            }
        }
        val rest = mSubtrees(s.drop(1))
        MTree(s(0), rest._1) -> rest._2
    }

    def createMTree(s:String): MTree[Char] = createMTreeAux(s)._1
}

object DemoMTree extends App {
    val a = MTree( 0, List(MTree(1, List(MTree(3), MTree(4)))))
    println(a.countNodes)
    println(a)


    println(MTree.createMTree("afg^^c^bd^e^^^").toString())
}
