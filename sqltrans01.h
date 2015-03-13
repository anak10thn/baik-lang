// //////////////////////////////////////////////////////////////////////
// Penerjemah SQL untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia
// //////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <sys/stat.h>


/* TRUE FALSE �̒�` */
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#define MAX_STRING_LEN  300


enum
{
  _SQLEND,      //10

  _SQLLABEL,    //11

  _SQL_AND,      /* ���� */
  _SQL_OR,       /* �������� */
  _SQL_NOT,      /* �ے� */

  _SQL_EOF,      /* �t�@�C���̏I�[ */

/* �\���ȊO�̃f�[�^ */
  TYPE_SQL_NUM,   /* 12 ���� */
  TYPE_SQL_IDENT, /* 13 �ϐ������邢�́A���x���� */
  TYPE_SQL_STR,   /* 14 ������ */
  TYPE_SQL_SYM,   /* 15 ���ꕶ�� */

/* ValLabel�֐��̑�O�����̃t���O */
  SQL_VAL_FLAG_START,      /* �T���؂̍쐬�i�������m�ہj     */
  SQL_VAL_FLAG_SEARCH_R,   /* �T���؂���f�[�^�������ǂݍ��� */
  SQL_VAL_FLAG_SEARCH_W,   /* �T���؂���f�[�^�������������� */
  SQL_VAL_FLAG_END,        /* �T���؂̏����i����������j     */
};


typedef struct
{
  /* ��L�ɒ�`���Ă���f�[�^���i�[����ϐ� */
  int type;

  /* �\���ȊO�̃f�[�^�̏ꍇ�́A���̃f�[�^������ϐ��Q */
  union{
    int num;                      /* ���� */
    char ident[MAX_IDENT_LEN];    /* �ϐ��� or ���x���� */
    char string[MAX_STRING_LEN];  /* ������ */
    char symbol;                  /* ���ꕶ�� */
  }detail;

} SQL_LEX_T;
/* �P����i�[����\���́B�i�[��S������̂�getlex�֐�
 * �P��́u�\���v�u�����v�u�ϐ��� or ���x�����v�u������v�u���ꕶ���v��
 * 5�̒��̂����ꂩ���������B�\���ȊO��������A
 * ���̃f�[�^���擾����B
 */

typedef struct
{
  int pt;        /* ���ݎ��s���Ă���ʒu */
  int back_pt;   /* �ߋ����s�����ʒu */
  char *source;  /* ���s���ׂ��v���O���� */
} SQL_S_ADDR;
/* ���s���̃v���O�����̈ʒu�������\���́B
 * source[pt] �ɂ��A���ݎ��s���v���O�����̈ʒu�������B
 */

///* ��L2�̍\���̂̃O���[�o�� */
//SQL_LEX_T sql_lex;  /* getlex�֐����Ă΂ꂽ���ɒl��������� */
//SQL_S_ADDR sql_pg;  /* ���ݎ��s���Ă���v���O�����̈ʒu��\�� */


typedef struct _sql_val_label
{
  struct _sql_val_label *left;   /* ���̃f�[�^�̃|�C���^ */
  struct _sql_val_label *right;  /* �E�̃f�[�^�̃|�C���^ */

  char ident[MAX_IDENT_LEN]; /* �ϐ����������̓��x���� */
  int data;                  /* �ϐ��̒l�������̓��x���̈ʒu */

} SQL_VAL_LABEL;
/* VAL_LABEL�\���̂́AValLabel�֐��ŊǗ������ 
 * ���̍\���̂́A�v���O�����Ɏg�p�����ϐ��⃉�x��������
 * �񕪒T���؂ɂ��Ǘ������B
 */

typedef struct
{

  SQL_LEX_T sql_lex;  /* getlex�֐����Ă΂ꂽ���ɒl��������� */
  SQL_S_ADDR sql_pg;  /* ���ݎ��s���Ă���v���O�����̈ʒu��\�� */
  char c;

} PARSING;

