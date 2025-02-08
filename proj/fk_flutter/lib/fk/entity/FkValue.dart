import 'package:fixnum/src/int64.dart';
import 'package:fk_flutter/fk/entity/FkPbValue.pb.dart';

class FkValue {
  static FkPbValue toInt32(int value) {
    final v = FkPbValue();
    v.int32Val = value;
    return v;
  }
  static FkPbValue toInt64(Int64 value) {
    final v = FkPbValue();
    v.int64Val = value;
    return v;
  }

  static FkPbValue toFloat(double value) {
    final v = FkPbValue();
    v.floatVal = value.toDouble();
    return v;
  }

  static FkPbValue toDouble(double value) {
    final v = FkPbValue();
    v.doubleVal = value.toDouble();
    return v;
  }

  static FkPbValue valueOf(String value) {
    final v = FkPbValue();
    v.strVal = value;
    return v;
  }
}
