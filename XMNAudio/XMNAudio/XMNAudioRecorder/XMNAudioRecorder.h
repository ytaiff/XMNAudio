//
//  XMNAudioRecorder.h
//  XMNAudioRecorder
//
//  Created by XMFraker on 16/6/23.
//  Copyright © 2016年 XMFraker. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "XMNAudioEncoder.h"

/** 录音错误类型 */
typedef NS_ENUM(NSUInteger, XMNAudioRecorderErrorCode) {
    /** 未知的错误类型 */
    XMNAudioRecorderErrorCodeUnkonwn = 0,
    /** 文件相关错误类型 创建文件失败,打开文件失败等 */
    XMNAudioRecorderErrorCodeFile,
    /** 队列相关错误 */
    XMNAudioRecorderErrorCodeQueue,
    /** AudioSession相关错误 */
    XMNAudioRecorderErrorCodeSession,
};

@class XMNAudioRecorder;
@protocol XMNAudioRecorderDelegate <NSObject>

/** 录音成功后回调 */
- (void)didRecordFinishWithRecorder:(XMNAudioRecorder * _Nonnull)recorder;
/** 录音失败后的回调 */
- (void)recorder:(XMNAudioRecorder * _Nonnull )recorder didRecordError:(NSError * _Nullable)error;

@end

@interface XMNAudioRecorder : NSObject
{
    @public
    //音频输入队列
    AudioQueueRef				_audioQueue;
    //音频输入数据format
    AudioStreamBasicDescription	_recordFormat;
}

/** 最大录音文件大小 */
@property (nonatomic, assign) unsigned long maxFileSize;

/** 最大录音时长 */
@property (nonatomic, assign) double maxSeconds;

/** 判断是否正在录音 */
@property (nonatomic, assign, readonly, getter=isRecording) BOOL recording;

/**
 *  设置录音采样率  默认 8000
 *  必须在startRecording 之前设置
 *  convertType = XMNAudioConvertTypeAMR 时 必须设置为8000
 */
@property (atomic, assign) NSUInteger sampleRate;

/**
 *  buffer 缓冲几秒的录音数据 默认.5f
 *  必须在startRecording 之前设置
 */
@property (atomic, assign) double bufferDurationSeconds;

/** 录音转换类型 */
@property (nonatomic, assign) XMNAudioEncoderType convertType;

/** 录音回调代理 */
@property (nonatomic, weak, nullable)   id<XMNAudioRecorderDelegate> delegate;

/** 存放录音文件的目录
 *  默认存放在 app/document/com.XMFraker.XMNAudioRecorder/目录下
 */
@property (nonatomic, copy, nullable)   NSString *filePath;

/** 录音的文件名 */
@property (nonatomic, copy, readonly, nonnull)   NSString *filename;


/** 录音成功后的block回调
 *  同 XMNAudioRecorderDelegate didRecordFinishWithRecorder
 */
@property (nonatomic, copy, nullable)   void(^recordFinishBlock)(XMNAudioRecorder * _Nonnull recorder);

/**
 *  录音失败后的block回调
 *  同 XMNAudioRecorderDelegate - (void)recorder:(XMNAudioRecorder *)recorder didRecordError:(NSError *)error
 */
@property (nonatomic, copy, nullable)   void(^recordErrorBlock)(XMNAudioRecorder * _Nonnull recorder, NSError * _Nullable error);

/**
 *  创建XMNAudioRecorder实例
 *
 *  @param filePath 存放录音文件的目录
 *
 *  @return
 */
- (instancetype _Nullable)initWithFilePath:(NSString * _Nullable)filePath;

/**
 *  开始录音功能
 *  随机生成32为字符串 并使用MD5加密
 */
- (void)startRecording;

/**
 *  开始录音功能
 *
 *  @param filename 指定录音文件的名称
 */
- (void)startRecordingWithFileName:(NSString * _Nullable)filename;

/**
 *  停止录音功能
 */
- (void)stopRecording;

@end
