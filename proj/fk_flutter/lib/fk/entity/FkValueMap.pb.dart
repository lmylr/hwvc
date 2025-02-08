//
//  Generated code. Do not modify.
//  source: FkValueMap.proto
//
// @dart = 2.12

// ignore_for_file: annotate_overrides, camel_case_types, comment_references
// ignore_for_file: constant_identifier_names, library_prefixes
// ignore_for_file: non_constant_identifier_names, prefer_final_fields
// ignore_for_file: unnecessary_import, unnecessary_this, unused_import

import 'dart:core' as $core;

import 'package:protobuf/protobuf.dart' as $pb;

import 'FkPbValue.pb.dart' as $6;

class FkValueMap extends $pb.GeneratedMessage {
  factory FkValueMap({
    $core.Map<$core.String, $6.FkPbValue>? value,
  }) {
    final $result = create();
    if (value != null) {
      $result.value.addAll(value);
    }
    return $result;
  }
  FkValueMap._() : super();
  factory FkValueMap.fromBuffer($core.List<$core.int> i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromBuffer(i, r);
  factory FkValueMap.fromJson($core.String i, [$pb.ExtensionRegistry r = $pb.ExtensionRegistry.EMPTY]) => create()..mergeFromJson(i, r);

  static final $pb.BuilderInfo _i = $pb.BuilderInfo(_omitMessageNames ? '' : 'FkValueMap', package: const $pb.PackageName(_omitMessageNames ? '' : 'com.alimin.fk.pb'), createEmptyInstance: create)
    ..m<$core.String, $6.FkPbValue>(1, _omitFieldNames ? '' : 'value', entryClassName: 'FkValueMap.ValueEntry', keyFieldType: $pb.PbFieldType.OS, valueFieldType: $pb.PbFieldType.OM, valueCreator: $6.FkPbValue.create, valueDefaultOrMaker: $6.FkPbValue.getDefault, packageName: const $pb.PackageName('com.alimin.fk.pb'))
    ..hasRequiredFields = false
  ;

  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.deepCopy] instead. '
  'Will be removed in next major version')
  FkValueMap clone() => FkValueMap()..mergeFromMessage(this);
  @$core.Deprecated(
  'Using this can add significant overhead to your binary. '
  'Use [GeneratedMessageGenericExtensions.rebuild] instead. '
  'Will be removed in next major version')
  FkValueMap copyWith(void Function(FkValueMap) updates) => super.copyWith((message) => updates(message as FkValueMap)) as FkValueMap;

  $pb.BuilderInfo get info_ => _i;

  @$core.pragma('dart2js:noInline')
  static FkValueMap create() => FkValueMap._();
  FkValueMap createEmptyInstance() => create();
  static $pb.PbList<FkValueMap> createRepeated() => $pb.PbList<FkValueMap>();
  @$core.pragma('dart2js:noInline')
  static FkValueMap getDefault() => _defaultInstance ??= $pb.GeneratedMessage.$_defaultFor<FkValueMap>(create);
  static FkValueMap? _defaultInstance;

  @$pb.TagNumber(1)
  $core.Map<$core.String, $6.FkPbValue> get value => $_getMap(0);
}


const _omitFieldNames = $core.bool.fromEnvironment('protobuf.omit_field_names');
const _omitMessageNames = $core.bool.fromEnvironment('protobuf.omit_message_names');
