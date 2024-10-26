object LongestCommonSubsequence {
  import scala.collection.mutable.ArrayBuffer
  def longestCommonSubsequence(text1: String, text2: String): Int = {
    var dp = ArrayBuffer.fill(text1.length)(ArrayBuffer.fill(text2.length)(0))
    
    def safeDP(i:Int)(j:Int) = {
      if i < 0 || j < 0 || i >= text1.length || j >= text2.length then 0
      else dp(i)(j)
    }

    for{
      i <- 0 until text1.length
      j <- 0 until text2.length
    } do {
      dp(i)(j) = if text1(i) == text2(j) then safeDP(i-1)(j-1) +1
      else math.max(safeDP(i-1)(j), safeDP(i)(j-1))
    }
    
    dp(text1.length-1)(text2.length-1)
  }
}
