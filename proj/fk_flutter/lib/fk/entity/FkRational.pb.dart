//
//  Generated code. Do not modify.
//  source: FkRational.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:core' as $core;

import 'package:protobuf/protobuf.dart' as $pb;

class FkRational extends $pb.GeneratedMessage {
  factory FkRational({
    $core.int? num,
    $core.int? den,
  }) {
    final $result = create();
    if (num != null) {
      $result.num = num;
    }
    if (den != null) {
      $result.den = den;
    }
    return $result;
  }
  FkRational._() : super();
  factory FkRational.fromBuffer($core.List<$core.int> i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromBuffer(i, r);
  factory FkRational.fromJson($core.String i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromJson(i, r);

  static final $pb.BuilderInfo _i = $pb.BuilderInfo(_omitMessageNames ? '' : 'FkRational', package: const $pb.PackageName(_omitMessageNames ? '' : 'com.alimin.fk.pb'), createEmptyInstance: create)
    ..a<$core.int>(1, _omitFieldNames ? '' : 'num', $pb.PbFieldType.O3)
    ..a<$core.int>(2, _omitFieldNames ? '' : 'den', $pb.PbFieldType.O3)
    ..hasRequiredFields = false
  ;

  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.deepCopy] instead. '
  'Will be removed in next major version')
  FkRational clone() => FkRational()..mergeFromMessage(this);
  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.rebuild] instead. '
  'Will be removed in next major version')
  FkRational copyWith(void Function(FkRational) updates) => super.copyWith((message) => updates(message as FkRational)) as FkRational;

  $pb.BuilderInfo get info_ => _i;

  @$core.pragma('dart2js:noInline')
  static FkRational create() => FkRational._();
  FkRational createEmptyInstance() => create();
  static $pb.PbList<FkRational> createRepeated() => $pb.PbList<FkRational>();
  @$core.pragma('dart2js:noInline')
  static FkRational getDefault() => _defaultInstance ??= $pb.GeneratedMessage.$_defaultFor<FkRational>(create);
  static FkRational? _defaultInstance;

  @$pb.TagNumber(1)
  $core.int get num => $_getIZ(0);
  @$pb.TagNumber(1)
  set num($core.int v) { $_setSignedInt32(0, v); }
  @$pb.TagNumber(1)
  $core.bool hasNum() => $_has(0);
  @$pb.TagNumber(1)
  void clearNum() => clearField(1);

  @$pb.TagNumber(2)
  $core.int get den => $_getIZ(1);
  @$pb.TagNumber(2)
  set den($core.int v) { $_setSignedInt32(1, v); }
  @$pb.TagNumber(2)
  $core.bool hasDen() => $_has(1);
  @$pb.TagNumber(2)
  void clearDen() => clearField(2);
}


const _omitFieldNames = $core.bool.fromEnvironment('protobuf.omit_field_names');
const _omitMessageNames = $core.bool.fromEnvironment('protobuf.omit_message_names');
