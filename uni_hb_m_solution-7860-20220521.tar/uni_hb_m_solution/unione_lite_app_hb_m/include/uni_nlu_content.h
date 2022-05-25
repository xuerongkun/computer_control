#ifndef INC_UNI_NLU_CONTENT_H_
#define INC_UNI_NLU_CONTENT_H_

typedef struct {
  uni_u32 key_word_hash_code; /* 存放识别词汇对应的hashcode */
  uni_u8  nlu_content_str_index; /* 存放nlu映射表中的索引，实现多个识别词汇可对应同一个nlu，暂支持256条，如果不够换u16 */
  char    *hash_collision_orginal_str /* 类似Java String equal，当hash发生碰撞时，赋值为识别词汇，否则设置为NULL */;
} uni_nlu_content_mapping_t;

enum {
  eCMD_wakeup_uni,
  eCMD_exitUni,
  eCMD_GOGO,
  eCMD_BACK,
  eCMD_STOP,
  eCMD_LEFT,
  eCMD_RIGHT,
  eCMD_HAPPY,
  eCMD_ww,
  eCMD_ss,
  eCMD_aa,
  eCMD_gg,
  eCMD_nn,
  eCMD_h_e_l_p_jx_0,
};

const char* const g_nlu_content_str[] = {
[eCMD_wakeup_uni] = "{\"asr\":\"你好小智\",\"cmd\":\"wakeup_uni\",\"pcm\":\"[103, 104, 105]\"}",
[eCMD_exitUni] = "{\"asr\":\"你先歇一会吧\",\"cmd\":\"exitUni\",\"pcm\":\"[107]\"}",
[eCMD_GOGO] = "{\"asr\":\"向前冲吧\",\"cmd\":\"GOGO\",\"pcm\":\"[109]\"}",
[eCMD_BACK] = "{\"asr\":\"向后退吧\",\"cmd\":\"BACK\",\"pcm\":\"[110]\"}",
[eCMD_STOP] = "{\"asr\":\"请你停下\",\"cmd\":\"STOP\",\"pcm\":\"[111]\"}",
[eCMD_LEFT] = "{\"asr\":\"向左旋转\",\"cmd\":\"LEFT\",\"pcm\":\"[112]\"}",
[eCMD_RIGHT] = "{\"asr\":\"向右旋转\",\"cmd\":\"RIGHT\",\"pcm\":\"[113]\"}",
[eCMD_HAPPY] = "{\"asr\":\"生日快乐\",\"cmd\":\"HAPPY\",\"pcm\":\"[114]\"}",
[eCMD_ww] = "{\"asr\":\"你多大了\",\"cmd\":\"ww\",\"pcm\":\"[115]\"}",
[eCMD_ss] = "{\"asr\":\"你的爸爸是谁\",\"cmd\":\"ss\",\"pcm\":\"[116]\"}",
[eCMD_aa] = "{\"asr\":\"你能干什么\",\"cmd\":\"aa\",\"pcm\":\"[117]\"}",
[eCMD_gg] = "{\"asr\":\"你有驾照吗\",\"cmd\":\"gg\",\"pcm\":\"[118]\"}",
[eCMD_nn] = "{\"asr\":\"天气不错\",\"cmd\":\"nn\",\"pcm\":\"[119]\"}",
[eCMD_h_e_l_p_jx_0] = "{\"asr\":\"语音导航\",\"cmd\":\"h_e_l_p_jx_0\",\"pcm\":\"[120]\"}",
};

/*TODO perf sort by hashcode O(logN), now version O(N)*/
const uni_nlu_content_mapping_t g_nlu_content_mapping[] = {
  {2835566009U/*你好小智*/, eCMD_wakeup_uni, NULL},
  {4252414048U/*小智同学*/, eCMD_wakeup_uni, NULL},
  {3202934839U/*下午好小智*/, eCMD_wakeup_uni, NULL},
  {505059847U/*你先歇一会吧*/, eCMD_exitUni, NULL},
  {3928484526U/*向前冲吧*/, eCMD_GOGO, NULL},
  {4238244592U/*向后退吧*/, eCMD_BACK, NULL},
  {3188976174U/*请你停下*/, eCMD_STOP, NULL},
  {3249308299U/*向左旋转*/, eCMD_LEFT, NULL},
  {909017600U/*向右旋转*/, eCMD_RIGHT, NULL},
  {3832328108U/*生日快乐*/, eCMD_HAPPY, NULL},
  {84529692U/*你多大了*/, eCMD_ww, NULL},
  {3121818694U/*你的爸爸是谁*/, eCMD_ss, NULL},
  {1760168717U/*你能干什么*/, eCMD_aa, NULL},
  {2498903541U/*你有驾照吗*/, eCMD_gg, NULL},
  {1304517813U/*天气不错*/, eCMD_nn, NULL},
  {3688209423U/*语音导航*/, eCMD_h_e_l_p_jx_0, NULL},
  {2436444297U/*帮助*/, eCMD_h_e_l_p_jx_0, NULL},
  {222837372U/*怎么用*/, eCMD_h_e_l_p_jx_0, NULL},
  {1766680370U/*不会用*/, eCMD_h_e_l_p_jx_0, NULL},
};

#endif
