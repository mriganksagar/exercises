package root

// P46 (**) Truth tables for logical expressions.

object TruthTableP46 {
    def and(a: Boolean, b: Boolean): Boolean = a && b
    def or (a: Boolean, b: Boolean): Boolean = a || b
    def nand(a: Boolean, b: Boolean): Boolean = !(a && b) 
    def nor(a: Boolean, b: Boolean): Boolean = !(a||b)
    def equ(a: Boolean, b : Boolean) = a == b
    def xor(a: Boolean, b: Boolean): Boolean = !equ(a, b)
    

}

object LogicCode extends App{

}