package root

import scala.math.Numeric.Implicits._
import scala.math.Ordering.Implicits._

object ArithmeticUtilities {
  // finding primes
  val primes = {
    def sieve(l: LazyList[Int]): LazyList[Int] = {
      l.head #:: sieve(l.tail.filter(_ % l.head != 0))
    }
    sieve(LazyList.from(2))
  }

  // fixed point function
  def fixedPoint[T: Numeric](f: T => T, x: T, tolerance: T): T = {
    val next = f(x)
    if ((next - x).abs <= tolerance) then next
    else fixedPoint(f, next, tolerance)
  }

}

object ArithmeticQuestions {
  import ArithmeticUtilities._

  // p31 an integer is prime or not
  def isPrime(number: Int): Boolean =
    primes.takeWhile(_ <= number).contains(number)

  // alternatively, by checking only primes till root of number and then divisibility
  def isPrime_efficient(n: Int): Boolean = if n < 2 then false
  else primes takeWhile { _ <= Math.sqrt(n) } forall { e => n % e != 0 }

  // p32 greatest common divisor of two positive integers
  def findGreatestCommonDivisor(a: Int, b: Int): Int =
    if a > b then findGreatestCommonDivisor(b, a)
    else if a == 0 then b
    else findGreatestCommonDivisor(b % a, a)

  // p33 find if two positive integers are coprime
  def findCoPrime(a: Int, b: Int): Boolean =
    findGreatestCommonDivisor(a, b) == 1

  // p34 eulers totient function
  def findEulersTotientFunction(a: Int) =
    (1 until a).count(e => findCoPrime(a, e))

  // p35 find prime factors of a number
  def findPrimeFactors(n: Int): List[Int] = {
    def findprimelist(
        i: Int,
        acc: List[Int],
        nextPrimes: LazyList[Int]
    ): List[Int] = {
      if i == 1 then acc.reverse
      else if i % nextPrimes.head == 0 then
        findprimelist(i / nextPrimes.head, nextPrimes.head :: acc, nextPrimes)
      else findprimelist(i, acc, nextPrimes.tail)
    }

    findprimelist(n, Nil, primes)
  }

  // p36 determine prime factors with multiplicity
  // i can modify p35 a little or use encoding run length from list questions
  def findPrimeFactorsWithMultiplicity(n: Int): List[(Int, Int)] = {
    def formatWithMultiplicity[T](
        l: List[T],
        acc: List[(T, Int)]
    ): List[(T, Int)] = {
      if l == Nil then acc.reverse
      else {
        val (first, last) = l.span(_ == l.head)
        formatWithMultiplicity(last, (first.head, first.size) :: acc)
      }
    }

    formatWithMultiplicity(findPrimeFactors(n), Nil)
  }

  // p37 calculate eulers totient function improved using prime factors
  def eulersTotientUsingPrimes(n: Int): Int = {
    findPrimeFactorsWithMultiplicity(n).foldLeft(n) { (acc, e) =>
      acc * (e._1 - 1) / e._1
    }
  }

  // p39 calculate prime in a given range
  def primesInRange(lower: Int, higher: Int): List[Int] = {
    primes.dropWhile { _ < lower }.takeWhile { _ <= higher }.toList
  }

  // p40 goldbach's conjecture
  def goldbach(n: Int): Option[(Int, Int)] = {
    primes.takeWhile(_ < n).find { p => isPrime(n - p) }.map(p => (p, n - p))
  }

  // p41 given a range print all goldbach's conjecture
  def printGoldBach(r: Range): Unit = for {
    a <- r
    if a % 2 == 0
  } println(goldbach(a).get)
}

object TestArithmeticQuestions extends App {
  import ArithmeticQuestions._
  import ArithmeticUtilities._

  // test is prime numbers
  def testIsPrimeNumber(): Unit = {
    println(primes.take(100).toList)
    println(isPrime(541))
    println(isPrime(531))
  }

  // test g c f
  def testFindGreatestCommonDivisor(): Unit = {
    println(findGreatestCommonDivisor(13, 12))
    println(findGreatestCommonDivisor(134, 67))
    println(findGreatestCommonDivisor(123, 123))
  }

  // test is two numbers co prime
  def testFindCoPrime(): Unit = {
    println(findCoPrime(5, 50))
    println(findCoPrime(51, 50))
  }

  // test prime factors
  def testFindPrimeFactors(): Unit = {
    println(findPrimeFactors(315))
    println(findPrimeFactors(133))
  }

  // test prime factors with Multiplicity
  def testFindPrimeFactorsWithMultiplicity(): Unit = {
    println(findPrimeFactorsWithMultiplicity(315))
    println(findPrimeFactorsWithMultiplicity(133))
  }

  // test eulers totient function
  def testEulersTotient(): Unit = {
    println(findEulersTotientFunction(66))
    println(findEulersTotientFunction(234))
  }

  // test eulers totient function using primes
  def testEulersTotientUsingPrimes(): Unit = {
    println(eulersTotientUsingPrimes(66))
    println(eulersTotientUsingPrimes(234))
  }

  // test goldback list 
  def testGoldbachList():Unit = {
    printGoldBach(Range(19,91))
  }

  // testIsPrimeNumber()
  // testFindGreatestCommonDivisor()
  // testFindCoPrime()
  // testFindPrimeFactors()
  // testFindPrimeFactorsWithMultiplicity()
  // testEulersTotient()
  // testEulersTotientUsingPrimes()
  // testGoldbachList()
}
