/*
 * segment.h
 *
 *  Created on: 2025/04/18
 *      Author: uchuu
 */

/*  segment.h  ―― 曲率テーブル・再生モードの共有定義 --------------- */
#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>
#include <math.h>

/* 最大マーカー数 (区間は MAX_SEG-1) */
#define MAX_SEG     160
//#define MAX_RECORDS 10000

/* 再生 / 記録モード */
typedef enum { MODE_RECORD = 0, MODE_PLAY } RunMode;

/* 区間情報テーブル */
typedef struct {
    float R;        /* 曲率半径 [mm] */
    float speed;    /* 推奨 basespeed */
} SegmentInfo;

/* 位置構造体 (円フィッティング用) */
typedef struct {
    float x;
    float y;
} Position;

/* ---- グローバル変数（どこか 1 ファイルで実体定義） ---------------- */
extern volatile RunMode  runMode;
extern SegmentInfo       segTbl[MAX_SEG-1];
extern uint8_t           segCnt;

extern uint16_t  marker_idx[MAX_SEG];
extern uint8_t   marker_cnt;

extern uint16_t  record_index;
extern volatile uint8_t marker_flag;



extern uint8_t curSeg;

/* プロトタイプ */
void BuildSegmentTable(void);
float decideSpeed(float R);
void fit_circle_kasa(Position* pts, uint16_t n, float* cx, float* cy, float* R);
void odom_update(uint16_t i);

#endif /* SEGMENT_H */
