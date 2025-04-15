val scala3Version = "3.5.2"

lazy val scala99problems = project
  .in(file("."))
  .settings(
    name := "scala99problems",
    version := "0.1.0-SNAPSHOT",

    scalaVersion := scala3Version,

    libraryDependencies ++= Seq(
      "org.scalameta" %% "munit" % "1.0.0" % Test,
      "org.scalatest" %% "scalatest" % "3.2.18" % Test
    )    
  )

lazy val dsa = project
  .in(file("dsa"))
  .settings(
    name := "dsa",
    scalaVersion := scala3Version,
    // other settings
    libraryDependencies += "org.scalatest" %% "scalatest" % "3.2.18" % Test
  )