/////////////////////////////////////////////////////////////
//  This file was generated automatically by xml_to_h.exe
//  Copyrights: Percello LTD. 2007-2008
//  Date:       9/21/2011 5:07:37 PM
/////////////////////////////////////////////////////////////


#define ipsec_PREFIX              0xBE420000

#define IPSEC_STATUS                                                                    (ipsec_PREFIX+0xA480)   // 32 bits
#define ipsec_status__ipsec_data_rdy0__start_bit                                                            0
#define ipsec_status__ipsec_data_rdy0__mask                                                          0x1   // [0]
#define ipsec_status__ipsec_data_rdy1__start_bit                                                            1
#define ipsec_status__ipsec_data_rdy1__mask                                                          0x2   // [1]
#define ipsec_status__ipsec_sadb_acc_grant__start_bit                                                       2
#define ipsec_status__ipsec_sadb_acc_grant__mask                                                     0x4   // [2]
#define ipsec_status__ipsec_engine_rdy__start_bit                                                           3
#define ipsec_status__ipsec_engine_rdy__mask                                                         0x8   // [3]
#define ipsec_status__ipsec_res_alm_full__start_bit                                                         4
#define ipsec_status__ipsec_res_alm_full__mask                                                       0x10   // [4]
#define ipsec_status__ipsec_res_alm_empty__start_bit                                                        5
#define ipsec_status__ipsec_res_alm_empty__mask                                                      0x20   // [5]
#define ipsec_status__ipsec_res_empty__start_bit                                                            6
#define ipsec_status__ipsec_res_empty__mask                                                          0x40   // [6]
#define ipsec_status__ipsec_desc_alm_full__start_bit                                                        7
#define ipsec_status__ipsec_desc_alm_full__mask                                                      0x80   // [7]
#define ipsec_status__ipsec_desc_alm_empty__start_bit                                                       8
#define ipsec_status__ipsec_desc_alm_empty__mask                                                     0x100   // [8]
#define ipsec_status__ipsec_error_code__start_bit                                                           9
#define ipsec_status__ipsec_error_code__mask                                                         0xe00   // [11:9]
#define ipsec_status__ipsec_Reserved__start_bit                                                             12
#define ipsec_status__ipsec_Reserved__mask                                                           0xffff000   // [27:12]
#define IPSEC_CONTROL                                                                   (ipsec_PREFIX+0xA440)   // 32 bits
#define ipsec_control__ipsec_cpu_descriptor__start_bit                                                      0
#define ipsec_control__ipsec_cpu_descriptor__mask                                                    0x1   // [0]
#define ipsec_control__ipsec_ipsec_en__start_bit                                                            1
#define ipsec_control__ipsec_ipsec_en__mask                                                          0x2   // [1]
#define ipsec_control__ipsec_illegal_en__start_bit                                                          2
#define ipsec_control__ipsec_illegal_en__mask                                                        0x4   // [2]
#define ipsec_control__ipsec_dma__w_endianess___start_bit                                                        3
#define ipsec_control__ipsec_dma_w_endianess___mask                                                      0x7f8   // [10:3]
#define ipsec_control__ipsec_dma_w_reverse__start_bit                                                           11
#define ipsec_control__ipsec_dma_w_reverse__mask                                                         0x800   // [11]
#define ipsec_control__ipsec_dma_r_endianess___start_bit                                                        12
#define ipsec_control__ipsec_dma_r_endianess___mask                                                      0xff000   // [19:12]
#define ipsec_control__ipsec_dma_r_reverse__start_bit                                                           20
#define ipsec_control__ipsec_dma_r_reverse__mask                                                         0x100000   // [20]
#define ipsec_control__ipsec_seq_num_size__start_bit                                                        21
#define ipsec_control__ipsec_seq_num_size__mask                                                      0x200000   // [21]
#define ipsec_control__ipsec_sadb_acc_cont__start_bit                                                       22
#define ipsec_control__ipsec_sadb_acc_cont__mask                                                     0x400000   // [22]
#define ipsec_control__ipsec_self_test_req__start_bit                                                       23
#define ipsec_control__ipsec_self_test_req__mask                                                     0x1800000   // [24:23]
#define ipsec_control__ipsec_reserve__start_bit                                                             25
#define ipsec_control__ipsec_reserve__mask                                                           0xfe000000   // [31:25]
#define IPSEC_INTERRUPT_ENABLE                                                          (ipsec_PREFIX+0xA408)   // 10 bits
#define ipsec_Interrupt_Enable__ipsec_data_rdy0__start_bit                                                  0
#define ipsec_Interrupt_Enable__ipsec_data_rdy0__mask                                                0x1   // [0]
#define ipsec_Interrupt_Enable__ipsec_data_rdy1__start_bit                                                  1
#define ipsec_Interrupt_Enable__ipsec_data_rdy1__mask                                                0x2   // [1]
#define ipsec_Interrupt_Enable__ipsec_sadb_acc_grant__start_bit                                             2
#define ipsec_Interrupt_Enable__ipsec_sadb_acc_grant__mask                                           0x4   // [2]
#define ipsec_Interrupt_Enable__ipsec_engine_rdy__start_bit                                                 3
#define ipsec_Interrupt_Enable__ipsec_engine_rdy__mask                                               0x8   // [3]
#define ipsec_Interrupt_Enable__ipsec_res_alm_full__start_bit                                               4
#define ipsec_Interrupt_Enable__ipsec_res_alm_full__mask                                             0x10   // [4]
#define ipsec_Interrupt_Enable__ipsec_res_alm_empty__start_bit                                              5
#define ipsec_Interrupt_Enable__ipsec_res_alm_empty__mask                                            0x20   // [5]
#define ipsec_Interrupt_Enable__ipsec_res_empty__start_bit                                                  6
#define ipsec_Interrupt_Enable__ipsec_res_empty__mask                                                0x40   // [6]
#define ipsec_Interrupt_Enable__ipsec_desc_alm_full__start_bit                                              7
#define ipsec_Interrupt_Enable__ipsec_desc_alm_full__mask                                            0x80   // [7]
#define ipsec_Interrupt_Enable__ipsec_desc_alm_empty__start_bit                                             8
#define ipsec_Interrupt_Enable__ipsec_desc_alm_empty__mask                                           0x100   // [8]
#define ipsec_Interrupt_Enable__ipsec_error__start_bit                                                      9
#define ipsec_Interrupt_Enable__ipsec_error__mask                                                    0x200   // [9]
#define IPSEC_INTERRUPT_STATUS                                                          (ipsec_PREFIX+0xA420)   // 10 bits
#define ipsec_interrupt_status__ipsec_data_rdy0__start_bit                                                  0
#define ipsec_interrupt_status__ipsec_data_rdy0__mask                                                0x1   // [0]
#define ipsec_interrupt_status__ipsec_data_rdy1__start_bit                                                  1
#define ipsec_interrupt_status__ipsec_data_rdy1__mask                                                0x2   // [1]
#define ipsec_interrupt_status__ipsec_sadb_acc_grant__start_bit                                             2
#define ipsec_interrupt_status__ipsec_sadb_acc_grant__mask                                           0x4   // [2]
#define ipsec_interrupt_status__ipsec_engine_rdy__start_bit                                                 3
#define ipsec_interrupt_status__ipsec_engine_rdy__mask                                               0x8   // [3]
#define ipsec_interrupt_status__ipsec_res_alm_full__start_bit                                               4
#define ipsec_interrupt_status__ipsec_res_alm_full__mask                                             0x10   // [4]
#define ipsec_interrupt_status__ipsec_res_alm_empty__start_bit                                              5
#define ipsec_interrupt_status__ipsec_res_alm_empty__mask                                            0x20   // [5]
#define ipsec_interrupt_status__ipsec_res_empty__start_bit                                                  6
#define ipsec_interrupt_status__ipsec_res_empty__mask                                                0x40   // [6]
#define ipsec_interrupt_status__ipsec_desc_alm_full__start_bit                                              7
#define ipsec_interrupt_status__ipsec_desc_alm_full__mask                                            0x80   // [7]
#define ipsec_interrupt_status__ipsec_desc_alm_empty__start_bit                                             8
#define ipsec_interrupt_status__ipsec_desc_alm_empty__mask                                           0x100   // [8]
#define ipsec_interrupt_status__ipsec_error__start_bit                                                      9
#define ipsec_interrupt_status__ipsec_error__mask                                                    0x200   // [9]
#define IPSEC_THRESHOLD                                                                 (ipsec_PREFIX+0xA410)   // 29 bits
#define ipsec_threshold__ipsec_desc_almost_full__start_bit                                                  0
#define ipsec_threshold__ipsec_desc_almost_full__mask                                                0xff   // [7:0]
#define ipsec_threshold__ipsec_desc_almost_empty__start_bit                                                 8
#define ipsec_threshold__ipsec_desc_almost_empty__mask                                               0xff00   // [15:8]
#define ipsec_threshold__ipsec_result_almost_full__start_bit                                                16
#define ipsec_threshold__ipsec_result_almost_full__mask                                              0x1f0000   // [20:16]
#define ipsec_threshold__ipsec_NA__start_bit                                                                21
#define ipsec_threshold__ipsec_NA__mask                                                              0xe00000   // [23:21]
#define ipsec_threshold__ipsec_result_almost_empty__start_bit                                               24
#define ipsec_threshold__ipsec_result_almost_empty__mask                                             0x1f000000   // [28:24]
#define IPSEC_START_0                                                                   (ipsec_PREFIX+0xA200)   // 0 bits
#define IPSEC_START_1                                                                   (ipsec_PREFIX+0xA204)   // 0 bits
#define IPSEC_INPUT_RDY_0                                                               (ipsec_PREFIX+0xA208)   // 0 bits
#define IPSEC_INPUT_RDY_1                                                               (ipsec_PREFIX+0xA20c)   // 0 bits
#define IPSEC_AES_CCMED_0                                                               (ipsec_PREFIX+0xA210)   // 0 bits
#define IPSEC_AES_CCMED_1                                                               (ipsec_PREFIX+0xA214)   // 0 bits
#define IPSEC_CPU_ENDIANESS                                                             (ipsec_PREFIX+0xA218)   // 0 bits
#define ipsec_cpu_endianess__ipsec_w_endianess___start_bit                                                  0
#define ipsec_cpu_endianess__ipsec_w_endianess___mask                                                0xff   // [7:0]
#define ipsec_cpu_endianess__ipsec_w_reverse__start_bit                                                     8
#define ipsec_cpu_endianess__ipsec_w_reverse__mask                                                   0x100   // [8]
#define ipsec_cpu_endianess__ipsec_r_endianess___start_bit                                                  9
#define ipsec_cpu_endianess__ipsec_r_endianess___mask                                                0x1fe00   // [16:9]
#define ipsec_cpu_endianess__ipsec_r_reverse__start_bit                                                     17
#define ipsec_cpu_endianess__ipsec_r_reverse__mask                                                   0x80   // [7]
#define IPSEC_SHA_KEY_START_1                                                           (ipsec_PREFIX+0xA21c)   // 0 bits
#define IPSEC_SPI_0                                                                     (ipsec_PREFIX+0xA220)   // 32 bits
#define IPSEC_SPI_1                                                                     (ipsec_PREFIX+0xA224)   // 32 bits
#define IPSEC_LENGTH_0                                                                  (ipsec_PREFIX+0xA228)   // 32 bits
#define IPSEC_LENGTH_1                                                                  (ipsec_PREFIX+0xA22C)   // 32 bits
#define IPSEC_SADB_SIZE                                                                 (ipsec_PREFIX+0xA230)   // 8 bits
#define IPSEC_ANTI_REPLAY_WIN_SIZE                                                      (ipsec_PREFIX+0xA234)   // 8 bits
#define IPSEC_MONITOR_BUS                                                               (ipsec_PREFIX+0xA238)   // 16 bits
#define IPSEC_ENGINE_EN                                                                 (ipsec_PREFIX+0xA23C)   // 1 bits
#define IPSEC_DA_0                                                                      (ipsec_PREFIX+0xA240)   // 32 bits
#define IPSEC_DA_1                                                                      (ipsec_PREFIX+0xA244)   // 32 bits
#define IPSEC_SP_0                                                                      (ipsec_PREFIX+0xA248)   // 2 bits
#define ipsec_sp_0__ipsec_esp_ah__start_bit                                                                 0
#define ipsec_sp_0__ipsec_esp_ah__mask                                                               0x1   // [0]
#define ipsec_sp_0__ipsec_ipsec_raw__start_bit                                                              1
#define ipsec_sp_0__ipsec_ipsec_raw__mask                                                            0x2   // [1]
#define IPSEC_SP_1                                                                      (ipsec_PREFIX+0xA24C)   // 2 bits
#define ipsec_sp_1__ipsec_esp_ah__start_bit                                                                 0
#define ipsec_sp_1__ipsec_esp_ah__mask                                                               0x1   // [0]
#define ipsec_sp_1__ipsec_ipsec_raw__start_bit                                                              1
#define ipsec_sp_1__ipsec_ipsec_raw__mask                                                            0x2   // [1]
#define IPSEC_CLEAR                                                                     (ipsec_PREFIX+0xA250)   // 1 bits
