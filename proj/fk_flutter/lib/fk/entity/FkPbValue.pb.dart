//
//  Generated code. Do not modify.
//  source: FkPbValue.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:core' as $core;

import 'package:fixnum/fixnum.dart' as $fixnum;
import 'package:protobuf/protobuf.dart' as $pb;

class FkPbValue extends $pb.GeneratedMessage {
  factory FkPbValue({
    $core.int? int32Val,
    $fixnum.Int64? int64Val,
    $core.double? floatVal,
    $core.double? doubleVal,
    $core.String? strVal,
  }) {
    final $result = create();
    if (int32Val != null) {
      $result.int32Val = int32Val;
    }
    if (int64Val != null) {
      $result.int64Val = int64Val;
    }
    if (floatVal != null) {
      $result.floatVal = floatVal;
    }
    if (doubleVal != null) {
      $result.doubleVal = doubleVal;
    }
    if (strVal != null) {
      $result.strVal = strVal;
    }
    return $result;
  }
  FkPbValue._() : super();
  factory FkPbValue.fromBuffer($core.List<$core.int> i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromBuffer(i, r);
  factory FkPbValue.fromJson($core.String i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromJson(i, r);

  static final $pb.BuilderInfo _i = $pb.BuilderInfo(_omitMessageNames ? '' : 'FkPbValue', package: const $pb.PackageName(_omitMessageNames ? '' : 'com.alimin.fk.pb'), createEmptyInstance: create)
    ..a<$core.int>(1, _omitFieldNames ? '' : 'int32Val', $pb.PbFieldType.O3, protoName: 'int32Val')
    ..aInt64(2, _omitFieldNames ? '' : 'int64Val', protoName: 'int64Val')
    ..a<$core.double>(3, _omitFieldNames ? '' : 'floatVal', $pb.PbFieldType.OF, protoName: 'floatVal')
    ..a<$core.double>(4, _omitFieldNames ? '' : 'doubleVal', $pb.PbFieldType.OD, protoName: 'doubleVal')
    ..aOS(5, _omitFieldNames ? '' : 'strVal', protoName: 'strVal')
    ..hasRequiredFields = false
  ;

  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.deepCopy] instead. '
  'Will be removed in next major version')
  FkPbValue clone() => FkPbValue()..mergeFromMessage(this);
  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.rebuild] instead. '
  'Will be removed in next major version')
  FkPbValue copyWith(void Function(FkPbValue) updates) => super.copyWith((message) => updates(message as FkPbValue)) as FkPbValue;

  $pb.BuilderInfo get info_ => _i;

  @$core.pragma('dart2js:noInline')
  static FkPbValue create() => FkPbValue._();
  FkPbValue createEmptyInstance() => create();
  static $pb.PbList<FkPbValue> createRepeated() => $pb.PbList<FkPbValue>();
  @$core.pragma('dart2js:noInline')
  static FkPbValue getDefault() => _defaultInstance ??= $pb.GeneratedMessage.$_defaultFor<FkPbValue>(create);
  static FkPbValue? _defaultInstance;

  @$pb.TagNumber(1)
  $core.int get int32Val => $_getIZ(0);
  @$pb.TagNumber(1)
  set int32Val($core.int v) { $_setSignedInt32(0, v); }
  @$pb.TagNumber(1)
  $core.bool hasInt32Val() => $_has(0);
  @$pb.TagNumber(1)
  void clearInt32Val() => clearField(1);

  @$pb.TagNumber(2)
  $fixnum.Int64 get int64Val => $_getI64(1);
  @$pb.TagNumber(2)
  set int64Val($fixnum.Int64 v) { $_setInt64(1, v); }
  @$pb.TagNumber(2)
  $core.bool hasInt64Val() => $_has(1);
  @$pb.TagNumber(2)
  void clearInt64Val() => clearField(2);

  @$pb.TagNumber(3)
  $core.double get floatVal => $_getN(2);
  @$pb.TagNumber(3)
  set floatVal($core.double v) { $_setFloat(2, v); }
  @$pb.TagNumber(3)
  $core.bool hasFloatVal() => $_has(2);
  @$pb.TagNumber(3)
  void clearFloatVal() => clearField(3);

  @$pb.TagNumber(4)
  $core.double get doubleVal => $_getN(3);
  @$pb.TagNumber(4)
  set doubleVal($core.double v) { $_setDouble(3, v); }
  @$pb.TagNumber(4)
  $core.bool hasDoubleVal() => $_has(3);
  @$pb.TagNumber(4)
  void clearDoubleVal() => clearField(4);

  @$pb.TagNumber(5)
  $core.String get strVal => $_getSZ(4);
  @$pb.TagNumber(5)
  set strVal($core.String v) { $_setString(4, v); }
  @$pb.TagNumber(5)
  $core.bool hasStrVal() => $_has(4);
  @$pb.TagNumber(5)
  void clearStrVal() => clearField(5);
}


const _omitFieldNames = $core.bool.fromEnvironment('protobuf.omit_field_names');
const _omitMessageNames = $core.bool.fromEnvironment('protobuf.omit_message_names');
