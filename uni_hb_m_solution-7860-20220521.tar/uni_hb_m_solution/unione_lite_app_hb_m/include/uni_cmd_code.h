#ifndef INC_UNI_CMD_CODE_H_
#define INC_UNI_CMD_CODE_H_

typedef struct {
  uni_u8      cmd_code; /* cmd code fro send base on SUCP */
  const char  *cmd_str; /* action string on UDP */;
} cmd_code_map_t;

const cmd_code_map_t g_cmd_code_arry[] = {
  {0x0, "wakeup_uni"},
  {0x1, "exitUni"},
  {0x2, "GOGO"},
  {0x3, "BACK"},
  {0x4, "STOP"},
  {0x5, "LEFT"},
  {0x6, "RIGHT"},
  {0x7, "HAPPY"},
  {0x8, "ww"},
  {0x9, "ss"},
  {0xa, "aa"},
  {0xb, "gg"},
  {0xc, "nn"},
  {0xd, "h_e_l_p_jx_0"},
};

#endif
