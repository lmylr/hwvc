import 'package:flutter/cupertino.dart';
import "package:stack_trace/stack_trace.dart";

class Logcat {
  static void debug(String msg, {String tag = "FilmKilns"}) {
    final frame = Trace.current().frames[1];
    debugPrint("$tag: [${frame.member}: ${frame.line}] $msg");
  }
}