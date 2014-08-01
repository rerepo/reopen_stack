LOCAL_PATH := $(call my-dir)

mod_stack_preproc := true

#-----------------------------------------------------------------------
# macro for output file name and makefile name
#
OUTNAME1=enb_cpuh
OUTNAME2=enb_cpul
SY_DIR=./obj
CPUH_OBJ=./obj/cpuh
CPUL_OBJ=./obj/cpul
CPU_CM_OBJ=./obj/cpucm

STOPTS=-DENB 

#-----------------------------------------------------------------------
# macros for td specific options
#

# MTSS defines
MTOPTS=-DSS -DSS_MT -UCONRD -UNOFILESYS
MTOPTS1=-DSS -DSS_MT -UCONRD -DNOFILESYS -DSS_DBLK_FREE_RTN
MTOPTS2=-DSS -DSS_MT -DCONRD -DSS_DBLK_FREE_RTN

#Handover Support flag
LTE_HO_SUPPORT = -DLTE_HO_SUPPORT
BRDCM_ONLY_CPUL = -DBC_MEM_COUNT
TENB_AS_SECURITY = -DTENB_AS_SECURITY
RLOG_OPTS = -DRLOG_ENABLE_TEXT_LOGGING -DRLOG_DEBUG_MODE  -URLOG_USE_CIRCULAR_BUFFER -URLOG_USE_TTI_LOGGING
# EnodeB End to End Compile Options
CMENBE2EOPTS=-DCMINET_BSDCOMPAT -DSS_TICKS_SEC=100 -DCMFILE_REORG_1\
          -DCM_INET2 -DCMFILE_REORG_2 -DSSINT2 -DCMKV2 -DHI_MULTI_THREADED\
          -DYS_ENB_CFG -DSS_PERF -DSS_WL_REGION=1 -DNO_ERRCLS -DNOERRCHK\
          -DDEBUGP -ULTE_ENB_PERF -UVE_PERF_MEAS -UCM_PASN_DBG -DREL_850\
          -UUE_RAD_CAP -ULTE_START_UL_DL_DATA -DSS_FLOAT -DRGR_RRM_TICK\
          -UUSE_PURE -DSLES9_PLUS -DTA_NEW -DSI_NEW -DRGR_SI_SCH\
          -DVE_SRB2_SUPPORT -UVE_SUPPORT_RLC_UM_MODE -UNOFILESYS -ULTE_LNX_AFFINITY\
          -DRGR_V1 -DLTEMAC_MIMO $(LTE_HO_SUPPORT) -DRS -DKW_BG_DL_PROC -DDISABLE_RRCSEC\
          -DKW_BG_UL_PROC -DWR_SB_SCTP -DLTERRC_REL9 -UCTF_VER3 -USSI_DEBUG_LEVEL1\
          -DMME_LDBAL -DSZ_ENB -DEGTP_U_REL_9 -DLEGV2 -DTFU_UPGRADE -DRGR_CQI_REPT \
          -DRGR_V2 -UMAC_SCH_STATS -DPHY_ERROR_LOGING -UWR_UL_PWR \
          -USS_DIAG -DSZTV2 -DBRDCM -DSS_MT_TMR -DSS_M_PROTO_REGION -DWR_DETECT_RLF\
          $(BRDCM_ONLY_CPUL) -DSZTV2 -DBRDCM -DSS_MT_TMR -DSS_M_PROTO_REGION \
          -USS_MEM_CORRUPTION_DETECTION $(BRDCM_ONLY_CPUL) -DBRDCM_DEBUG -UL2_LOGGING_ENABLED -UBRCM_PROFILE \
	  -DREVIEW -DTENB_RTLIN_CHANGES -DTENB_SPLIT_ARCH_SUPPORT -DTENB_SPLIT_ARCH \
	  -DSZTV3 -DS1AP_REL9A6 -UBRDCM_L2LOG_ENABLE -DWR_DL_CQI -DCZTV1 -DTENB_DISABLE_DL_ZBC -DSS_RBUF\
	  $(TENB_AS_SECURITY) -USPACC_RAW -USPACC_SG -UPHY_SHUTDOWN_ENABLE -DBRDCM_BUGFIX -DLTEMAC_DRX -UE_TM -UCTF_VER3 -DWR_RSYS_KPI -DLTE_L2_MEAS\
	  -DREM_ENABLE -DCIPH_BATCH_PROC -DCPJ_V2 $(RLOG_OPTS) -DBRCM_ZBC -DTENB_FP -DWR_WATCHDOG -UUL_LA -UDL_LA -ULA_VER2 -DLTEMAC_SPS -DxBRDCM_SSI_MEM_LEAK_DEBUG_LEVEL1 -DxBRDCM_SSI_MEM_LEAK_DEBUG_LEVEL2
# The options below are used to pass on to the actual product compilations
# Just this one variable is passed for individual compilations and hence
# all the needed options are added from various other defined option macros


#All Convergence Layer  options
#LCLOPTS=-DLCLCL -DSM -DCL
TFUOPTS=-DTFU_VER_2 -UTFU_TDD -DLCTFU


# All LTE MAC product options
CRGOPTS= -DLCNHLICRG -DLCCRG -DLCRGUICRG
CRGOPTS1= -DLCNHLICRG -DLCCRG -DLCRGUICRG -DRG
RGUOPTS=-DRG -DKW -DLCKWLIRGU -DLCRGU -DLCRGUIRGU -DCCPU_OPT -DLWLCKWLIRGU -DLWLCRGUIRGU
LRGOPTS=-DLCSMMILRG -DLCLRG -DSM -DLCRGMILRG -DRM_INTF -DRGM_LWLC -DRGM_LC
RGROPTS=-DLCWRLIRGR -DLCRGR -DLWLCWRLIRGR -DLCRGUIRGR
RGRSEUMOPTS=-DLCWRLIRGR -DLCRGR -DLWLCWRLIRGR -DLCRGUIRGR
RGOPTS=-DRG -DRG_PHASE2_SCHED $(RGUOPTS) $(CRGOPTS) $(LRGOPTS) $(RGROPTS)\
        $(TFUOPTS) -URG_DEBUG -UTTI_PROC -UPROC_DL -USCH_TTI_PROC -UTOM\
        -UPAL_MAC_PROC -UUL_PROC_MAC -DLCRGLITFU -DLTEMAC_RGU_PAD

# All LTE EGTP-U product options
EGTOPTS=-DEG -DLCEGT -DLCEGUIEGT -DCCPU_OPT -DLCEULIEGT
LEGOPTS=-DLCSMMILEG -DLCLEG -DSM -DEG -DLCEGMILEG -DLCSMEGMILEG
EGOPTS=-DEG $(EGTOPTS) $(LEGOPTS) -UEG_DEBUG -DLCEGLIHIT 



#All RLC product options
CKWOPTS=-DLCNHLICKW -DLCCKW -DLCKWUICKW
KWUOPTS=-DKW -DNH -DLCKWUIKWU -DLWLCKWUIKWU -DLCKWU -DLCNHLIKWU -DCCPU_OPT
LKWOPTS=-DSM -DKW -DLCKWMILKW -DLCLKW
LPJOPTS=-DSM -DPJ -DLCPJMILPJ -DLCLPJ
PJUVEOPTS=-DNH -DLCPJU  -DLCWRLIPJU -DLCPJUIPJU
PJUVESEUMOPTS=-DNH -DLCPJU  -DLCWRLIPJU -DLCPJUIPJU
PJUNHOPTS= -DPJ -DLCPJU -DLCNHLIPJU -DLCPJUIPJU
CPJOPTS=-DLCCPJ -DNH -DKW -DLCNHLICPJ -DLCPJUICPJ
KWOPTS=-DKW -DKW_PDCP $(CKWOPTS) $(KWUOPTS) $(CPJOPTS) $(LPJOPTS) $(LKWOPTS) $(RGUOPTS)\
        $(PJUNHOPTS) $(PJUVEOPTS) -URLC_STATUS_GEN -UUL_PROC_MAC -DLTE_HENB

#ALL RRC product options
LNHOPTS=-DNH -DSM -DLCLNH -DLCSMMILNH -DLCSMNHMILNH -DLCNHMILNH
NHUOPTS=-DLCNHU -DWR -DNX -DLCWRLINHU -DLCNHUINHU -DLCNXLINHU -DLWLCNHUINHU\
        -DLWLCNXLINHU -DLCNHMILNH -DLCSMNHMILNH
NHOPTS=-DNH $(LNHOPTS) $(NHUOPTS) $(CRGOPTS) $(CKWOPTS) $(CPJOPTS) $(KWUOPTS)\
        $(PJUNHOPTS) -DRX -DRNC_INTEG_CCPU 

#ALL RRC application product options
LWROPTS=-DWR -DSM -ULCLWR -ULCSMMILWR -ULCWRMILWR
CTFOPTS=-DLCCTF -DWR -DLCWRLICTF -DLCTFUICTF -DLCNHLICTF
WROPTS=-DWR -DLCCZT $(LWROPTS) $(NHUOPTS) $(CTFOPTS) $(RGROPTS) $(PJUVEOPTS)\
        $(SZTOPTS) $(EGTOPTS) $(CZTOPTS)

#Remaining CL and TFU options
TFOPTS=-DTF $(CTFOPTS) $(RGROPTS) -DLCTFU -DLCTFUITFU -DTFU_VER_2 -UTFU_TDD -DRG
TFOPTS1=-DTF $(CTFOPTS1) $(RGROPTS)

#All S1AP product options
SZTOPTS=-DSZ -DUZ -DLCUZLISZT -DLWLCUZLISZT -DLCSZUISZT -DLCSZT -DPTSZUISZT\
        -US1AP_REL851 -DLSZV1 -DSZTV1 -DSZTV2 -DSZTV3 -DCM_PASN_CRIT_HANDL
LSZOPTS=-DLCLSZ -DLCSCT -DSM -DSZ -DLCSMSZMILSZ  -DLCSZMILSZ
SZOPTS=-DSZ $(SZTOPTS) $(LSZOPTS) $(SCTOPTS) -DLCSZMILSZ -DSM \
	  -DSZ_ENB -DSZ_DYNAMIC_PEER -DSZ_USTA


#All X2AP options
CZTOPTS=-DCZ -DRS -DLCRSLICZT -DLWLCRSLICZT -DLCCZUICZT -DLCCZT -DPTCZUICZT
LCZOPTS=-DLCLCZ -DLCSCT -DSM -DCZ -DLCSMCZMILCZ  -DLCSZMILCZ
CZOPTS=-DCZ $(CZTOPTS) $(LCZOPTS) $(SCTOPTS) -DLCCZMILCZ -DSM \
        -DCZ_ENB -DCZ_DYNAMIC_PEER -DCZ_USTA

#All SCTP product options
LSBOPTS=-DLCLSB -DSM -DSB -DLSB4  -DLSB8 -DHI_REL_1_4
SCTOPTS=-DSB  -DLCSBUISCT -DLCSZLISCT -DLCCZLISCT
HITOPTS=-DLCSBLIHIT -DLCHIUIHIT -DHI_REL_1_4 -DLCEGLIHIT 
SBOPTS = $(LSBOPTS) $(HITOPTS) $(SCTOPTS) -DLCSBMILSB -DLCSMSBMILSB\
         -DSB_CHECKSUM -DSB_CHECKSUM_CRC

#All TUCL product options
LHIOPTS=-DLCHIMILHI -DSM -DLCLHI
HIOPTS= $(LHIOPTS) $(HITOPTS) -DHI -DLCHIMILHI -DSM -DLCSMHIMILHI -DEG

#ALL RRC product options
LRXOPTS=-DRX -DSM -DLCLRX

#Stack Manager Options
SMOPTS= -DLCSMMILCL -DLCCLMILCL

#-----------------------------------------------------------------------
# macros for sw and include directories
#
#CODEPATH=../..
CODEPATH := $(LOCAL_PATH)
#BSPPATH=/projectnew/BRDCM/CELIVERO_BSP_2_15/linux-3.0.1-source
BSPPATH := $(LOCAL_PATH)/l1/kernel-headers
#PHYPATH=$(CODEPATH)/ltephybrcm/L1_SRC_Files/host_sw/releases/LTE_L1_LTE_L1_1.14.11
PHYPATH := $(LOCAL_PATH)/l1
MT_DIR=$(CODEPATH)/mt
CM_DIR=$(CODEPATH)/cm
#RLOG_DIR=$(CODEPATH)/rlog/
RLOG_DIR=$(CODEPATH)/rlog
WR_DIR=$(CODEPATH)/enbapp/src

RM_DIR=$(CODEPATH)/lterrm/src
UR_DIR=$(CODEPATH)/lteclbrcm
NH_DIR=$(CODEPATH)/lterrc
SZ_DIR=$(CODEPATH)/s1ap
CZ_DIR=$(CODEPATH)/x2ap
SB_DIR=$(CODEPATH)/sctp
HI_DIR=$(CODEPATH)/tucl
EG_DIR=$(CODEPATH)/egtpu
RG_DIR=$(CODEPATH)/ltemac
KW_DIR=$(CODEPATH)/lterlc
PJ_DIR=$(CODEPATH)/ltepdcp
#REM_DIR=$(CODEPATH)/lteremapp/
REM_DIR=$(CODEPATH)/lteremapp
WATCHDOG_DIR=$(CODEPATH)/watchdog/
CPU_CMN_LIB=-L$(PHYPATH)/CPU_COMMONS/lib
CPU_L1_LIB= -L$(PHYPATH)/CPUL/LTE_L1/builds/rio -L/lib
PS_LIB=-L./lib

# Directory paths of CPU-H modules
CPU_H_DIR=$(CM_DIR) $(WR_DIR) $(NH_DIR) $(SZ_DIR) $(CZ_DIR) $(SB_DIR)\
          $(HI_DIR) $(EG_DIR) $(MT_DIR) 
CPU_L_DIR=$(CM_DIR) $(UR_DIR) $(RG_DIR) $(KW_DIR) $(PJ_DIR) $(MT_DIR) 



#-----------------------------------------------------------------------
# macros for compile and link options

LNXENV=-DSUNOS -DSS -DSS_MT -DANSI -D_GNU_SOURCE -DSS_LINUX -D_REENTRANT -D__EXTENSIONS__ \
    -DDEBUGNOEXIT

# compiler:
LNX_CC="mipsel-unknown-linux-gnu-gcc"
LNX_LD="mipsel-unknown-linux-gnu-gcc"
LNX_AR="ar"

#LNX_CFLAG_CPUL=" $(LNXCOPTS) -march=mips32 -mtune=mips32 -mips32"
#LNX_CFLAG_CPUH=" $(LNXCOPTS) -march=mips32r2 -mtune=mips32r2 -mips32r2"
LNX_CFLAG_CPUL=$(LNXCOPTS) -march=mips32 -mtune=mips32 -mips32
LNX_CFLAG_CPUH=$(LNXCOPTS) -march=mips32r2 -mtune=mips32r2 -mips32r2

LNX_GPP_CC="mipsel-unknown-linux-gnu-g++" 
LNX_GPP_LD="mipsel-unknown-linux-gnu-g++"

#LNXCOPTS="-g -pipe -pedantic -Wall -Wno-comment -Wshadow -Wcast-qual \
-Wstrict-prototypes -Wmissing-prototypes -fno-strict-aliasing -fsigned-char"

LNXCOPTS=-g -O3 -pipe -pedantic -Wall -Werror -Wno-comment -Wshadow -Wcast-qual \
	-fno-strict-aliasing -fsigned-char --std=c99

LNXLOPTSCPP=-g -pipe -pedantic -Wall -Werror -Wno-comment -Wshadow -Wcast-qual \
	-fno-strict-aliasing -fsigned-char -lstdc++

# object files:
# o     UNIX
OBJ=o                                    # object files, sunos

# linker options:
#LNXLOPTS= -EL -lpthread -lnsl -lrt -lm -export-dynamic
LNXLOPTS= -EL -lrt -lm -lpthread
# include options:
LNXIOPTS  =  -I$(MT_DIR) -I$(CM_DIR) -I$(EG_DIR) -I$(SZ_DIR) -I$(PJ_DIR)\
             -I$(KW_DIR) -I$(CZ_DIR) -I$(WR_DIR) -I$(UR_DIR) -I$(RM_DIR) -I$(HI_DIR)\
             -isystem $(PHYPATH)/CPU_COMMONS/externals/\
             -isystem $(PHYPATH)/CPU_COMMONS/includes/\
             -isystem $(PHYPATH)/CPUL/LTE_L1/externals/\
             -isystem $(PHYPATH)/CPUL/LTE_L1/includes/\
             -isystem $(BSPPATH)/usr/include/brcm/\
             -I$(MT_DIR)/security/ -I$(RLOG_DIR)

# compiler options:

# MTSS defines
CCLNXMTOPTS=$(DEBUGPOPTS) $(LNXENV) $(MTOPTS) $(CMOPTS) $(STOPTS) -DOP_SSI_SAM

# SM defines 
CCLNXSMOPTS= $(LNXENV) $(SMOPTS) $(CMOPTS) $(STOPTS)

# NH defines 
CCLNXNHOPTS=  $(LNXENV) $(NHOPTS) $(CMOPTS) $(STNHOPTS)

#KW defines
CCLNXKWOPTS= $(LNXENV) $(KWOPTS)  $(STOPTS) $(CMOPTS)

#PJ defines
CCLNXPJOPTS= $(LNXENV) $(KWOPTS)  $(STOPTS) $(CMOPTS)
#RG defines 
CCLNXRGOPTS= $(LNXENV) $(RGOPTS)  $(STOPTS) $(CMOPTS)

#TF defines 
CCLNXTFOPTS= $(LNXENV) $(TFOPTS) $(RGOPTS) $(STOPTS) $(CMOPTS)

#EG defines 
CCLNXEGOPTS= $(LNXENV) $(EGOPTS)  $(STOPTS) $(CMOPTS)

#SZ defines
CCLNXSZOPTS= $(LNXENV) $(SZOPTS)  $(STOPTS) $(CMOPTS)

#CZ defines
CCLNXCZOPTS= $(LNXENV) $(CZOPTS)  $(STOPTS) $(CMOPTS)

#WR defines 
CCLNXWROPTS= $(LNXENV) $(WROPTS)  $(STOPTS) $(CMOPTS)

#SB defines 
CCLNXSBOPTS= $(LNXENV) $(SBOPTS)  $(STOPTS) $(CMOPTS)

#HI defines 
CCLNXHIOPTS= $(LNXENV) $(HIOPTS)  $(STOPTS) $(CMOPTS)

#RRM defines 
CCLNXRMOPTS= $(LNXENV) $(RMOPTS)  $(STOPTS) $(CMOPTS)

#common options 
CCLNXCMOPTS= $(LNXENV) $(CMOPTS) $(SMOPTS) \
         $(MKUOPTS) $(CMKOPTS)  \
         $(CRLOPTS) $(RLUOPTS)  $(STOPTS) \
         $(CTCOPTS) $(TCUOPTS) $(LRXOPTS) 


LNXENBE2EBIN_BC_FROMPRE=enb_e2e_bc_blog
LNXENBE2EBIN_BC=enb_e2e_bc

BASENAME=enodeb_bc
MAKENAME=$(BASENAME).mak

BINLNXE2E_BC=lnx_e2e_bc
BINLNXE2E_BC_FROMPRE=lnx_e2e_bc_blog
LNXENBE2EPRE_BC=bc_prepro
BINLNXLINK2PS=lnx_link2ps
PRELNXE2E_BC=lnx_bc_pre


######################
# CUSTOM OPTIONS
######################
CREATE_ENB := YES
BLDENV := lnx_e2e_bc
OAM_ENABLE :=

CMOPTS=$(CMENBE2EOPTS)


#
#
# Linux Default GNU acceptance test build
#
acc:
	@echo "Compiling acc##################"
	@echo $(MAKENAME)
	@$(MAKE) -f $(MAKENAME) $(BLDENV)

$(BINLNXE2E_BC):$(CPUL_OBJ) $(CPUH_OBJ)
	@echo '*********************************************************' 
	@echo '              Building PHY AND CPU common Lib            ' 
	@echo '*********************************************************' 
	mkdir -p $(PHYPATH)/CPU_COMMONS/obj
	@$(MAKE) -C $(PHYPATH)/CPUL/LTE_L1/builds/rio/
	@echo '*********************************************************' 
	@echo '              Building PS                                '
	@echo '*********************************************************' 
	@$(MAKE) -f $(MAKENAME) $(LNXENBE2EBIN_BC) CC=$(LNX_CC) \
	LL=$(LNX_LD) CMOPTS='$(CMENBE2EOPTS)' 




#--------------------------------------------------------------#
#Makefile for product WR
#--------------------------------------------------------------#

#--------------------------------------------------------------#
#User macros (to be modified)
#--------------------------------------------------------------#

RrmFlags=-DRM_INTF -DRMU_LWLC -DRM_NPLC -DLWLCSMRMMILRM -UTCSMRMMILRM -DLCSMRMMILRM -DPTSMMILRM -LRM_NPLC

COPTS_NO_WARN=-g -O3 -pipe -pedantic -W -Wno-comment -Wshadow -Wcast-qual -fno-strict-aliasing -fsigned-char --std=c99 -march=mips32r2 -mtune=mips32r2 -mips32r2

ifeq (${BLD},seum)
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -UPTNXLIPJU -UPTWRLIRGR -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -UTA_NEW -USI_NEW -URGR_SI_SCH -DSS_MT_TMR $(RrmFlags)
else
ifeq (${BLD},picoseum)
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -UPTNXLIPJU -UPTWRLIRGR -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -UWR_PICO -UWR_WITHOUT_CNE -DWIRESHARK_LOG -UYS_PICO -DSI_NEW -DYS_PICO -DWR_PICO  -DSS_MT_TMR $(RrmFlags)
else
ifeq (${BLDENV},lnx_e2e_ms)
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -DPTNXLIPJU -DPTWRLIRGR -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DLCSMNHMILNH -DDG -UWR_DG_OAM -DVALIDATION_CHK -DWR_TEST_CODE -DWR_TEST_CLI -DENB_OVRLOAD -UMME_LDBAL -DSS_MT_TMR $(RrmFlags)
else
ifeq (${BLDENV},lnx_ms_pre)
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -DPTNXLIPJU -DPTWRLIRGR -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DLCSMNHMILNH -DDG -UWR_DG_OAM -DVALIDATION_CHK -DWR_TEST_CODE -DWR_TEST_CLI -DENB_OVRLOAD -UMME_LDBAL -DSS_MT_TMR $(RrmFlags)
else
ifeq (${BLDENV},lnx_ms_withoutdiag)
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -DPTNXLIPJU -DPTWRLIRGR -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DLCSMNHMILNH -DDG -UWR_DG_OAM -DVALIDATION_CHK -DWR_TEST_CODE -DWR_TEST_CLI -DENB_OVRLOAD -UMME_LDBAL -DSS_MT_TMR $(RrmFlags)
else
ifeq ($(BLDENV),lnx_e2e_bc)
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -DPTNXLIPJU -DPTWRLIRGR -DDEBUGP -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DLCSMNHMILNH -DDG -UWR_DG_OAM -DVALIDATION_CHK -DWR_TEST_CODE -DWR_TEST_CLI -DENB_OVRLOAD -UMME_LDBAL $(RrmFlags)
else
ifeq ($(BLDENV),lnx_bc_pre)
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -DPTNXLIPJU -DPTWRLIRGR -DDEBUGP -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DLCSMNHMILNH -DDG -UWR_DG_OAM -DVALIDATION_CHK -DWR_TEST_CODE -DWR_TEST_CLI -DENB_OVRLOAD -UMME_LDBAL $(RrmFlags)
else
CCwrFLAGS=-DWR_RELAY -DEU_DAT_APP -DEGTP_U -DNX -DPX -DUZ -DEU -DKW_PDCP -DKW -UPTNXLIPJU -UPTWRLIRGR -UTFU_TDD -DTFU_WRR_2 -DLCEGUIEGT -DLCWRLICTF -DLCWRLINHU -DxLCPJUIPJU -DLCWRLIRGR -ULTE_TDD -DTA_NEW -DSI_NEW -DRGR_SI_SCH -UWR_SM_LOG_TO_FILE  -DDG -UWR_DG_OAM -DVALIDATION_CHK -DWR_OAM_TEST -DWR_TEST_CODE -DWR_TEST_CLI -DENB_OVRLOAD -UMME_LDBAL -DSS_MT_TMR $(RrmFlags)
endif
endif
endif
endif
endif
endif
endif

ifeq ($(OAM_ENABLE),OAM_ENABLE)
CCwrFLAGS+= -DWR_RSYS_OAM -DWR_RSYS_KPI -DREM_ENABLE
endif 
ifeq ($(OAM_ENV),WR_RSYS_OAM)
CCwrFLAGS+= -DWR_RSYS_OAM
else
ifeq ($(OAM_ENV),WR_RSYS_OAM_SRC)
CCwrFLAGS+= -DWR_RSYS_OAM
endif
endif 


#CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DSZ -DYS -DRG -DPJ -DCZ 
#SS_DIR=../../mt
# NOTE: no use


######################


$(BLD_LNX_WR_E2E_OBJS1):
	@$(MAKE) -f wr.mak $(CPUH_OBJ)/libe2elnxwr.a COPTS=$(LNX_CFLAG_CPUH)  AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXWROPTS)' SMPOPTS='$(CCLNXSMOPTS)' \
	HIOPTS='$(HIOPTS)' SBOPTS='$(SBOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(WR_DIR)' IN_DIR='$(WR_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c" OAM_ENABLE='$(OAM_ENABLE)' 

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXWROPTS)'
# SMPOPTS='$(CCLNXSMOPTS)' [no]
# HIOPTS='$(HIOPTS)' [no]
# SBOPTS='$(SBOPTS)' [no]
# IOPTS='$(LNXIOPTS)'

#	$(CC)  -o$(OUT_DIR)/wr_sw_version.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \

###################### libe2elnxwr ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libe2elnxwr

enb_wr := enbapp/src

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_wr)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_mi.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_smm_enbapp.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_umm_lclctxtrel.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_umm_sec.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_umm_uecap.c,$(LOCAL_SRC_FILES))

ifeq ($(OAM_ENABLE),)
LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_smm_enbapp_cmnplatutils.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_smm_dyncfg.c,$(LOCAL_SRC_FILES))
endif
#$(warning LOCAL_SRC_FILES == $(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXWROPTS) $(CCwrFLAGS)

LOCAL_OBJECT_FLAGS_APPEND := $(call convert-object-flags,$(enb_wr)/wr_smm_rrc.o,-DLCSMNHMILNH -DLCLNH)

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_rlc.o,-DLCKWMILKW -DLCPJMILPJ -DLCLKW)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_mac.o,-DLCRGMILRG  -DLCLRG -DLCSMMILRG)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_s1ap.o,-DLCSMMILSZ -DLCLSZ -DSZ_ENB)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_x2ap.o $(enb_wr)/wr_plat.o,-DLCSMMILCZ -DLCLCZ -DCZ_ENB)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_sctp.o,-DLCSMSBMILSB -DLCLSB -DLSB4 -DLSB8)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_tucl.o,-DLCSMHIMILHI)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_egtp.o,-DLCSMMILEG -DLCLEG)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_enbapp_rsys.o,-DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM -UPTSMMILWR)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_enbapp_utils.o,-DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_rrm.o,-ULCSMMILWR  -ULCSWR -ULCWRMILWR)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_pdcp.o,-DLCSMMILPJ -DLCPJMILPJ -DLCLPJ)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_cl.o $(enb_wr)/wr_emm.o,-DLCSMYSMILYS -DLCYSMILYS -DLCLYS)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_ptmi.o,-DLCWRMILWR -DLWLCWRMILWR -DLWLCWR -DSM -DLCLWR)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_ex_ms.o,-ULCWR -DRG  -DLWLCWR  -DLWLCLWR   -DLCLWR -DSM)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_lwr.o,-DLWLCSMMILWR -DSM  -DLCLWR -DLWLCLWR -DLCSMMILWR)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_emm_anr.o $(enb_wr)/wr_emm_ecsfb_anr.o,-DDG)
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_wr)/wr_smm_tmr.o,-DLCSMYSMILYS -DLCYSMILYS -DLCLYS)

include $(BUILD_STATIC_LIBRARY)


######################

#	$(CC)  -o$(OUT_DIR)/hmac.$(OBJ) -I$(SS_DIR) $(COPTS_NO_WARN) $(IOPTS) $(POPTS) $(CCwrFLAGS) \

###################### libmtsec ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libmtsec

enb_sec := mt/security

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_sec)/*.c))

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(COPTS_NO_WARN) $(LNXIOPTS) $(CCLNXWROPTS) $(CCwrFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for RRM
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
_rm_CCrmFLAGS=-DRGM_LC -DRGM_LWLC -DLRM_LWLC -DRMU_LWLC -URMU_NPLC -DLWLCSMRMMILRM -DLCSMRMMILRM -DSM -DSS_MT_TMR -DRM_INTF

######################

$(BLD_LNX_RM_OBJS):
	@$(MAKE) -f rm.mak $(CPUH_OBJ)/librm.a COPTS='' AR=$(LNX_AR) \
        LOPTS='$(LNXLOPTS)' LOPTSCPP='$(LNXLOPTSCPP)' POPTS='$(CCLNXWROPTS)' SMPOPTS='$(CCLNXSMOPTS)'\
	HIOPTS='$(HIOPTS)' SBOPTS='$(SBOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(RM_DIR)' IN_DIR='$(RM_DIR)' \
        OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' SRC="c"  SRC1="cpp"  CC='$(LNX_GPP_CC) -c' LL='$(LNX_GPP_LD)' CM_INC='$(CM_INC)'
	mkdir -p ./lib/
	cp $(CPUH_OBJ)/librm.a ./lib/ 
	rm -rf $(CPUH_OBJ)/rm_* $(CPUH_OBJ)/librm.a

# COPTS=''
# LOPTS='$(LNXLOPTS)' [no]
# LOPTSCPP='$(LNXLOPTSCPP)' [no]
# POPTS='$(CCLNXWROPTS)'
# SMPOPTS='$(CCLNXSMOPTS)' [no]
# HIOPTS='$(HIOPTS)' [no]
# SBOPTS='$(SBOPTS)' [no]
# IOPTS='$(LNXIOPTS)'

#	$(CC)  $(COPTS) $(IOPTS) $(POPTS) $(CCrmFLAGS) $(IN_DIR)/rm.$(SRC1) -o \

###################### librm ######################
include $(CLEAR_VARS)

LOCAL_MODULE := librm

enb_rm := lterrm/src

#LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_rm)/*.c))
LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_rm)/*.cpp))
#LOCAL_SRC_FILES := $(filter-out $(enb_wr)/wr_mi.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNXIOPTS) $(CCLNXWROPTS) $(_rm_CCrmFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product cm - script generated.
#Only the $(CCcmFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

_cm_CCrmFLAGS=-DLRM_LWLC -DRMU_LWLC -URMU_NPLC -DRGM_LWLC -DLWLCSMRMMILRM -DLCSMRMMILRM -DSM -DRM_INTF
ifeq (${BLDENV}, lnx_e2e_ms)
_cm_CCcmFLAGS=-DSS_MT_TMR -DSS_FLOAT -ULTE_TDD -DRGR_V1 -DLSZV1 $(_cm_CCrmFLAGS)  #<---Insert cm specific defines here
else
ifeq (${BLDENV},lnx_ms_withoutdiag)
_cm_CCcmFLAGS=-DSS_MT_TMR -DSS_FLOAT -ULTE_TDD -DRGR_V1 -DLSZV1 $(_cm_CCrmFLAGS)  #<---Insert cm specific defines here
else
_cm_CCcmFLAGS=-DSS_MT_TMR -DSS_FLOAT -ULTE_TDD -DRGR_V1 -DLSZV1 -DVE_SB_SCTP $(_cm_CCrmFLAGS)#<---Insert cm specific defines here
endif
endif

ifeq (${BLDENV}, lnx_e2e_ms)
_cm_CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DKW_PDCP -DPJ -DSZ -DYS -DRG -DNH -UWR_SM_LOG_TO_FILE -DRGR_SI_SCH -UTA_NEW -DSI_NEW -DCZ $(_cm_CCrmFLAGS)
else
ifeq (${BLDENV},lnx_ms_withoutdiag)
_cm_CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DKW_PDCP -DPJ -DSZ -DYS -DRG -DNH -UWR_SM_LOG_TO_FILE -DRGR_SI_SCH -UTA_NEW -DSI_NEW -DCZ $(_cm_CCrmFLAGS)
else
_cm_CCsmFLAGS=-DHI -DSB -DEG -DWR -DKW -DKW_PDCP -DPJ -DSZ -DYS -DRG -DNH -UVE_SM_LOG_TO_FILE -DRGR_SI_SCH -DTA_NEW -DSI_NEW -DCZ $(_cm_CCrmFLAGS)
endif
endif

_cm_EGTOPTS=-DEG -DLCEGT -DLCEGUIEGT -DEGTP_U
_cm_LEGOPTS=-DLCSMMILEG -DLCLEG -DSM -DEG -DLCEGMILEG -DLCSMEGMILEG -DEGTP_U
_cm_LHIOPTS=-DLCHIMILHI -DSM -DLCLHI
_cm_HITOPTS=-DLCHIT -DLCSBLIHIT -DLCHIUIHIT -DHI_REL_1_4 -DLCEGLIHIT 
_cm_SCTOPTS=-DLCSCT 
_cm_LRGOPTS= -DLCSMMILRG -DLCLRG -DSM -DRG -DLCRGMILRG
_cm_LSBOPTS=-DLCLSB -DSM -DSB -DLSB4  -DLSB8 -DHI_REL_1_4
_cm_LSZOPTS=-DLCLSZ -DLCSCT -DSM -DSZ -DLCSMSZMILSZ  -DLCSZMILSZ -DSZ_ENB
_cm_SZTOPTS=-DSZ -DUZ -DLCUZLISZT -DLWLCUZLISZT -DLCSZUISZT -DLCSZT -DPTSZUISZT
_cm_LCZOPTS=-DLCLCZ -DLCSCT -DSM -DCZ -DLCSMCZMILCZ  -DLCCZMILCZ 
_cm_CZTOPTS=-DCZ -DRS -DLCRSLICZT -DLWLCRSLICZT -DLCCZUICZT -DLCCZT -DPTCZUICZT
_cm_RGROPTS=-DRG -DLCWRLIRGR -DLCRGR -DLWLCWRLIRGR -DLCRGUIRGR
_cm_CTFOPTS=-DLCCTF -DWR -DLCWRLICTF -DLCYSUICTF
_cm_LNHOPTS=-DNH -DSM -DLCLNH -DLCSMMILNH -DLCSMNHMILNH -DLCNHMILNH
_cm_NHUOPTS=-DLCNHU -DWR -DNX -DLCWRLINHU -DLCNXLINHU -DLCNHUINHU
_cm_LWROPTS=-DWR -DSM -DLCLWR -ULCSMMILWR -ULCWRMILWR -DWR_RELAY -DEU_DAT_APP
_cm_LPJOPTS=-DPJ -DSM -DLCLPJ -DLCSMMILPJ -DLCPJMILPJ -DKW_PDCP
_cm_LKWOPTS=-DKW -DSM -DLCLKW -DLCSMMILKW -DLCKWMILKW -DKW_PDCP
_cm_PJUVEOPTS=-DPJ -DLCPJU -DWR -DNX -DNH -DLCWRLIPJU -DLCPJUIPJU -DLCNHLIPJU
_cm_CKWOPTS=-DLCNHLICKW -DLCCKW -DLCKWUICKW -DKW -DNH
_cm_CPJOPTS=-DPJ -DLCCPJ -DNH -DLCNHLICPJ -DLCPJUICPJ
_cm_CRGOPTS= -DLCNHLICRG -DLCCRG -DLCRGUICRG -DRG
_cm_KWUOPTS=-DKW -DNH -DLCKWUIKWU -DLCKWU -DLCNHLIKWU -DCCPU_OPT
_cm_RGUOPTS= -DRG -DKW -DLCKWLIRGU -DLCRGU -DLCRGUIRGU -DCCPU_OPT
_cm_TFUOPTS=-UTFU_TDD -DTFU_VER_2 -DLCTFU 
_cm_LYSOPTS=-DYS -DLCLYS -DLCSMMILYS -DLCYSMILYS

######################

#
# Making Common Libraries
#
$(BLD_LNX_CM_OBJS):
	@$(MAKE) -f cm.mak $(CPUH_OBJ)/libcm.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXCMOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(CM_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)'  CM_INC='$(CM_INC)'
	@$(MAKE) -f rl.mak $(CPUH_OBJ)/librl COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
        LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXCMOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(RLOG_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' RLOG_INC='$(RLOG_INC)' SRC="c"
	@$(MAKE) -f cm.mak $(CPUL_OBJ)/libcm.a COPTS=$(LNX_CFLAG_CPUL) AR=$(LNX_AR) \
        LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXCMOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(CM_DIR)' \
        OUT_DIR='$(CPUL_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)'  CM_INC='$(CM_INC)'

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXCMOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC) -c -o $(OUT_DIR)/ckw.o $(COPTS) $(IOPTS) $(POPTS) $(CKWOPTS) $(CCcmFLAGS) $(IN_DIR)/ckw.c

###################### libcm ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libcm

enb_cm := cm

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_cm)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/cm_mem_wl.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/cm_ss.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/egt_util.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/lve.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/ss_ptsp.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXCMOPTS) $(_cm_CCcmFLAGS)

LOCAL_OBJECT_FLAGS_APPEND := $(call convert-object-flags,$(enb_cm)/ckw.o,$(_cm_CKWOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/sm_bdy1.o,$(_cm_CCsmFLAGS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/sm_ex_ms.o,$(_cm_CCsmFLAGS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/cm_tpt.o,$(_cm_SCTOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/cpj.o,$(_cm_CPJOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/crg.o,$(_cm_CRGOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/kwu.o,$(_cm_KWUOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lkw.o,$(_cm_LKWOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lnh.o,$(_cm_LNHOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lrg.o,$(_cm_LRGOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/nhu.o $(enb_cm)/nhu_pk.o $(enb_cm)/nhu_unpk.o $(enb_cm)/nhu_3gpk.o $(enb_cm)/nhu_3gunpk.o,-DNX $(_cm_NHUOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/pju.o,$(_cm_PJUVEOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/rgu.o,$(_cm_RGUOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/rgr.o,$(_cm_RGROPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/ctf.o,$(_cm_CTFOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/tfu.o,$(_cm_TFUOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lpj.o,$(_cm_LPJOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lys.o,$(_cm_LYSOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/leg.o,$(_cm_LEGOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/egt.o,$(_cm_EGTOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lhi.o,$(_cm_LHIOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/hit.o,$(_cm_HITOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lsb.o,$(_cm_LSBOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/sct.o,$(_cm_SCTOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lsz.o,$(_cm_LSZOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/szt.o $(enb_cm)/szt_pk.o $(enb_cm)/szt_3gpk.o $(enb_cm)/szt_unpk.o $(enb_cm)/szt_3gunpk.o,$(_cm_SZTOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lcz.o,$(_cm_LCZOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/czt.o $(enb_cm)/czt_pk.o $(enb_cm)/czt_unpk.o $(enb_cm)/rmu_pk.o $(enb_cm)/rmu_unpk.o $(enb_cm)/rmu.o $(enb_cm)/rgm.o $(enb_cm)/lrm.o,$(_cm_CZTOPTS))
#LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/.o,$(_cm_))

include $(BUILD_STATIC_LIBRARY)


######################

# cm cpul
#	@$(MAKE) -f cm.mak $(CPUL_OBJ)/libcm.a COPTS=$(LNX_CFLAG_CPUL) AR=$(LNX_AR) \
        LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXCMOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(CM_DIR)' \
        OUT_DIR='$(CPUL_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)'  CM_INC='$(CM_INC)'

# COPTS=$(LNX_CFLAG_CPUL)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXCMOPTS)'
# IOPTS='$(LNXIOPTS)'

###################### libcm_l ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libcm_l

enb_cm := cm

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_cm)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/cm_mem_wl.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/cm_ss.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/egt_util.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/lve.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_cm)/ss_ptsp.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUL) $(LNXIOPTS) $(CCLNXCMOPTS) $(_cm_CCcmFLAGS)

LOCAL_OBJECT_FLAGS_APPEND := $(call convert-object-flags,$(enb_cm)/ckw.o,$(_cm_CKWOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/sm_bdy1.o,$(_cm_CCsmFLAGS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/sm_ex_ms.o,$(_cm_CCsmFLAGS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/cm_tpt.o,$(_cm_SCTOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/cpj.o,$(_cm_CPJOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/crg.o,$(_cm_CRGOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/kwu.o,$(_cm_KWUOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lkw.o,$(_cm_LKWOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lnh.o,$(_cm_LNHOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lrg.o,$(_cm_LRGOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/nhu.o $(enb_cm)/nhu_pk.o $(enb_cm)/nhu_unpk.o $(enb_cm)/nhu_3gpk.o $(enb_cm)/nhu_3gunpk.o,-DNX $(_cm_NHUOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/pju.o,$(_cm_PJUVEOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/rgu.o,$(_cm_RGUOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/rgr.o,$(_cm_RGROPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/ctf.o,$(_cm_CTFOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/tfu.o,$(_cm_TFUOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lpj.o,$(_cm_LPJOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lys.o,$(_cm_LYSOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/leg.o,$(_cm_LEGOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/egt.o,$(_cm_EGTOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lhi.o,$(_cm_LHIOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/hit.o,$(_cm_HITOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lsb.o,$(_cm_LSBOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/sct.o,$(_cm_SCTOPTS))
LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lsz.o,$(_cm_LSZOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/szt.o $(enb_cm)/szt_pk.o $(enb_cm)/szt_3gpk.o $(enb_cm)/szt_unpk.o $(enb_cm)/szt_3gunpk.o,$(_cm_SZTOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/lcz.o,$(_cm_LCZOPTS))

LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/czt.o $(enb_cm)/czt_pk.o $(enb_cm)/czt_unpk.o $(enb_cm)/rmu_pk.o $(enb_cm)/rmu_unpk.o $(enb_cm)/rmu.o $(enb_cm)/rgm.o $(enb_cm)/lrm.o,$(_cm_CZTOPTS))
#LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_cm)/.o,$(_cm_))

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for RL
#-------------------------------------------------------------#

#rlPOSTPROCOPTS=-DSS_LINUX -DUSE_RLOG_DATA_TYPES 

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

######################

# rlog
#	@$(MAKE) -f rl.mak $(CPUH_OBJ)/librl COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
        LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXCMOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(RLOG_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' RLOG_INC='$(RLOG_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXCMOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC) $(COPTS) $(IOPTS) $(POPTS) $(IN_DIR)/rl_rlog.$(SRC) -rdynamic -o $(OUT_DIR)/rl_rlog.$(OBJ)

#	g++ $(rlPOSTPROCOPTS) $(rlPOSTPROCSRCS) -o	$(OUT_DIR)/rlogapp

###################### librl ######################
include $(CLEAR_VARS)

LOCAL_MODULE := librl

enb_rl := rlog

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_rl)/*.c))
#LOCAL_SRC_FILES := $(filter-out $(enb_rl)/rl_postproc.cpp,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXCMOPTS)

#LOCAL_OBJECT_FLAGS_APPEND += $(call convert-object-flags,$(enb_rl)/rl_rlog.o,-rdynamic)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product mt - script generated.
#Only the $(CCmtFLAGS) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCmtFLAGS=-UBIT_64 -DSS_MT_TMR -USS_LOGGER_SUPPORT -DEGTP_U#<---Insert mt specific defines here

######################

#
# making Multi Threaded SSI
#
$(BLD_LNX_SS_OBJS):
	@$(MAKE) -f mt.mak $(CPUH_OBJ)/libmt.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXMTOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(MT_DIR)' \
        OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)'  \
        CM_INC='$(CM_INC)' BLDENV='$(BLDENV)' SRC="c"
	@$(MAKE) -f mt.mak $(CPUL_OBJ)/libmt.a COPTS=$(LNX_CFLAG_CPUL) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXMTOPTS)' IOPTS='$(LNXIOPTS)' IN_DIR='$(MT_DIR)' \
        OUT_DIR='$(CPUL_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)'  \
        CM_INC='$(CM_INC)' BLDENV='$(BLDENV)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)'
# POPTS='$(CCLNXMTOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC) -c -o $(OUT_DIR)/mt_id.o $(COPTS) $(IOPTS) $(POPTS) $(CCmtFLAGS) $(IN_DIR)/mt_id.c

###################### enb_cpuh ######################
include $(CLEAR_VARS)

#LOCAL_MODULE := libmt
LOCAL_MODULE := enb_cpuh

enb_mt := mt

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_mt)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_mt)/ss_acc.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_mt)/ss_rtr.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_mt)/mt_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXMTOPTS) $(CCmtFLAGS)

LOCAL_STATIC_LIBRARIES += libe2elnxwr

LOCAL_STATIC_LIBRARIES += librm

LOCAL_STATIC_LIBRARIES += libcz
LOCAL_STATIC_LIBRARIES += libeg
LOCAL_STATIC_LIBRARIES += libhi
LOCAL_STATIC_LIBRARIES += libnh
LOCAL_STATIC_LIBRARIES += librl
LOCAL_STATIC_LIBRARIES += libsb
LOCAL_STATIC_LIBRARIES += libsz

#LOCAL_STATIC_LIBRARIES += libmt
LOCAL_STATIC_LIBRARIES += libmtsec

LOCAL_STATIC_LIBRARIES += libcm

#   new file:   enbapp/build/obj/cpuh/libcm.a
#   new file:   enbapp/build/obj/cpuh/libcpuh.a
#   new file:   enbapp/build/obj/cpuh/libcz.a
#   new file:   enbapp/build/obj/cpuh/libe2elnxwr.a
#   new file:   enbapp/build/obj/cpuh/libeg.a
#   new file:   enbapp/build/obj/cpuh/libhi.a
#   new file:   enbapp/build/obj/cpuh/libmt.a
#   new file:   enbapp/build/obj/cpuh/libnh.a
#   new file:   enbapp/build/obj/cpuh/librl.a
#   new file:   enbapp/build/obj/cpuh/libsb.a
#   new file:   enbapp/build/obj/cpuh/libsz.a

LOCAL_STATIC_LIBRARIES += libprcl1 libprcl1_ns
LOCAL_STATIC_LIBRARIES += libprc_commons

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

#mipsel-unknown-linux-gnu-gcc -g -o ./obj/enb_cpuh ./obj/cpuh/*.o    \
    -lprcl1 -lprcl1_ns -lprc_commons -lprcl1 -lprcl1_ns -lprc_commons -ldl \
    -EL -lrt -lm -lpthread -g -pipe -pedantic -Wall -Werror -Wno-comment -Wshadow -Wcast-qual -fno-strict-aliasing -fsigned-char -lstdc++ -L../../ltephybrcm/L1_SRC_Files/host_sw/releases/LTE_L1_LTE_L1_1.14.11/CPU_COMMONS/lib -L../../ltephybrcm/L1_SRC_Files/host_sw/releases/LTE_L1_LTE_L1_1.14.11/CPUL/LTE_L1/builds/rio -L/lib -L./lib -lrm
    
include $(BUILD_EXECUTABLE)


###################### enb_cpul ######################
include $(CLEAR_VARS)

#LOCAL_MODULE := libmt_l
LOCAL_MODULE := enb_cpul

enb_mt := mt

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_mt)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_mt)/ss_acc.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_mt)/ss_rtr.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_mt)/mt_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUL) $(LNXIOPTS) $(CCLNXMTOPTS) $(CCmtFLAGS)

LOCAL_STATIC_LIBRARIES += libur
LOCAL_STATIC_LIBRARIES += libpj
LOCAL_STATIC_LIBRARIES += libkw
LOCAL_STATIC_LIBRARIES += librg

#LOCAL_STATIC_LIBRARIES += libmt_l

LOCAL_STATIC_LIBRARIES += libcm_l

#   new file:   enbapp/build/obj/cpul/libcm.a
#   new file:   enbapp/build/obj/cpul/libcpul.a
#   new file:   enbapp/build/obj/cpul/libkw.a
#   new file:   enbapp/build/obj/cpul/libmt.a
#   new file:   enbapp/build/obj/cpul/libpj.a
#   new file:   enbapp/build/obj/cpul/librg.a
#   new file:   enbapp/build/obj/cpul/libur.a

LOCAL_STATIC_LIBRARIES += libprcl1 libprcl1_ns
LOCAL_STATIC_LIBRARIES += libprc_commons

LOCAL_LDFLAGS += -EL# -lrt -lm -lpthread
LOCAL_LDLIBS += -lrt -lpthread

#mipsel-unknown-linux-gnu-gcc -g -o ./obj/enb_cpul ./obj/cpul/*.o    \
    -lprcl1 -lprcl1_ns -lprc_commons -lprcl1 -lprcl1_ns -lprc_commons  \
    -L../../ltephybrcm/L1_SRC_Files/host_sw/releases/LTE_L1_LTE_L1_1.14.11/CPU_COMMONS/lib -L../../ltephybrcm/L1_SRC_Files/host_sw/releases/LTE_L1_LTE_L1_1.14.11/CPUL/LTE_L1/builds/rio -L/lib -EL -lrt -lm -lpthread -L./lib -lrm

include $(BUILD_EXECUTABLE)


#-------------------------------------------------------------#
#Makefile for product CZ - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

#product specific options should be identified.
CCczFLAGS=-DLCLCZ -DLCSCT -DCZ -DSM 

######################

$(BLD_LNX_CZ_OBJS1):
	@$(MAKE) -f cz.mak $(CPUH_OBJ)/libcz.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXCZOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(CZ_DIR)' IN_DIR='$(CZ_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)'
# POPTS='$(CCLNXCZOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC)  -o$(OUT_DIR)/cz_db.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCczFLAGS) \

###################### libcz ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libcz

enb_cz := x2ap

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_cz)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_cz)/cz_ex_pt.c,$(LOCAL_SRC_FILES))
# main()
LOCAL_SRC_FILES := $(filter-out $(enb_cz)/cz_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXCZOPTS) $(CCczFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product EG - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCegFLAGS=-DEGTP_U -DLCHIT -DLCEGLIHIT -DEU

######################

$(BLD_LNX_EG_OBJS1):
	@$(MAKE) -f eg.mak $(CPUH_OBJ)/libeg.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXEGOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(EG_DIR)' IN_DIR='$(EG_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXEGOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC)  -o$(OUT_DIR)/eg_cpm.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCegFLAGS) \

###################### libeg ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libeg

enb_eg := egtpu

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_eg)/*.c))
# main()
LOCAL_SRC_FILES := $(filter-out $(enb_eg)/eg_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXEGOPTS) $(CCegFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product HI - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CChiFLAGS=-USZ

######################

$(BLD_LNX_HI_OBJS1):
	@$(MAKE) -f hi.mak $(CPUH_OBJ)/libhi.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXHIOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(HI_DIR)' IN_DIR='$(HI_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXHIOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC)  -o$(OUT_DIR)/hi_bdy1.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CChiFLAGS) \

###################### libhi ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libhi

enb_hi := tucl

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_hi)/*.c))
# main()
LOCAL_SRC_FILES := $(filter-out $(enb_hi)/hi_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXHIOPTS) $(CChiFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product NH - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCnhFLAGS=-UKW -UPJ

######################

$(BLD_LNX_NH_OBJS1):
	@$(MAKE) -f nh.mak $(CPUH_OBJ)/libnh.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXNHOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(NH_DIR)' IN_DIR='$(NH_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXNHOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC)  -o$(OUT_DIR)/nh_brm.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCnhFLAGS) \

###################### libnh ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libnh

enb_nh := lterrc

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_nh)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_nh)/nh_ex_pt.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_nh)/nh_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXNHOPTS) $(CCnhFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product SB - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCsbFLAGS=

######################

$(BLD_LNX_SB_OBJS1):
	@$(MAKE) -f sb.mak $(CPUH_OBJ)/libsb.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXSBOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(SB_DIR)' IN_DIR='$(SB_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXSBOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC)  -o$(OUT_DIR)/sb_bdy1.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCsbFLAGS) \

###################### libsb ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libsb

enb_sb := sctp

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_sb)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_sb)/sb_ex_pt.c,$(LOCAL_SRC_FILES))
# main()
LOCAL_SRC_FILES := $(filter-out $(enb_sb)/sb_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXSBOPTS) $(CCsbFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product SZ - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCszFLAGS=-DLCLSZ -DLCSCT -DSZ -DSM -US1AP_REL851 -DLSZV1 -DS1AP_REL9A6

######################

$(BLD_LNX_SZ_OBJS1):
	@$(MAKE) -f sz.mak $(CPUH_OBJ)/libsz.a COPTS=$(LNX_CFLAG_CPUH) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXSZOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(SZ_DIR)' IN_DIR='$(SZ_DIR)' \
	OUT_DIR='$(CPUH_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUH)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXSZOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC)  -o$(OUT_DIR)/sz_db.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCszFLAGS) \

###################### libsz ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libsz

enb_sz := s1ap

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_sz)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_sz)/sz_dbr8.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_sz)/sz_dbr9.c,$(LOCAL_SRC_FILES))
# main()
LOCAL_SRC_FILES := $(filter-out $(enb_sz)/sz_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUH) $(LNXIOPTS) $(CCLNXSZOPTS) $(CCszFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product ib - script generated.
#Only the $(CCib) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCkwFLAGS= -UKW_PDCP -UNH -USM -DPTPJLIB -DLTE_HENB  \
       -UKW_BG_DL_PROC -UKW_BG_UL_PROC -DERRCLS_INT_PAR\
       -DSS_MT_TMR -DLCUDX -DLWLCKWULUDX -DLCKWULUDX

######################

$(BLD_LNX_KW_OBJS):
	@$(MAKE) -f kw_split.mak $(CPUL_OBJ)/libkw.a COPTS=$(LNX_CFLAG_CPUL) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXKWOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(KW_DIR)' IN_DIR='$(KW_DIR)' \
	OUT_DIR='$(CPUL_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"
	
# COPTS=$(LNX_CFLAG_CPUL)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXKWOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCkwFLAGS) $(IN_DIR)/kw_amm_ul.$(SRC) -o \

###################### libkw ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libkw

enb_kw := lterlc

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_kw)/*.c))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUL) $(LNXIOPTS) $(CCLNXKWOPTS) $(CCkwFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product ib - script generated.
#Only the $(CCib) may be modified.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCpjFLAGS= -UKW_PDCP -UNH -USM -DPJ -DPX -DPTPJLIB -DLTE_HENB  -DKW_BG_DL_PROC -DKW_BG_UL_PROC  -DSS_MT_TMR

# Product objects-------------------------------------------------------
#ifeq ($(SEC_FLAG),-DTENB_AS_SECURITY)
ifeq ($(TENB_AS_SECURITY),-DTENB_AS_SECURITY)
$(warning TENB_AS_SECURITY == $(TENB_AS_SECURITY))
endif

######################

$(BLD_LNX_PJ_OBJS):
	@$(MAKE) -f pj.mak $(CPUL_OBJ)/libpj.a COPTS=$(LNX_CFLAG_CPUL) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXPJOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(PJ_DIR)' IN_DIR='$(PJ_DIR)' \
	OUT_DIR='$(CPUL_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c" SEC_FLAG='$(TENB_AS_SECURITY)'
	
# COPTS=$(LNX_CFLAG_CPUL)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXPJOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCpjFLAGS) $(IN_DIR)/pj_lim.c -o \

###################### libpj ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libpj

enb_pj := ltepdcp

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_pj)/*.c))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUL) $(LNXIOPTS) $(CCLNXPJOPTS) $(CCpjFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product RG - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#
# Including RG_PHASE2_SCHED for supporting more than one schedulers 
# supported by mac
CCrgFLAGS=-DRGM_LC -DRGM_LWLC -DTFU_VER_2 -UTFU_TDD -USM -ULTE_TDD -DTF -DSS_FLOAT -DSS_MT_TMR \
           -URG_DEBUG -DxRG_PHASE2_SCHED -DxRGR_V1 -DxRG_UL_DELTA=2 -DLTEMAC_DLUE_TMGOPTMZ -DTENB_SPLIT_ARCH -DRM_INTF 

######################
 
$(BLD_LNX_RG_OBJS):
	@$(MAKE) -f rg.mak $(CPUL_OBJ)/librg.a COPTS=$(LNX_CFLAG_CPUL) AR=$(LNX_AR) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXRGOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(RG_DIR)' IN_DIR='$(RG_DIR)' \
	OUT_DIR='$(CPUL_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUL)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXRGOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC) -c  -o$(OUT_DIR)/rg_cfg.$(OBJ) $(COPTS) $(IOPTS) $(POPTS) $(CCrgFLAGS) \

###################### librg ######################
include $(CLEAR_VARS)

LOCAL_MODULE := librg

enb_rg := ltemac

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_rg)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_rg)/rg_ex_pt.c,$(LOCAL_SRC_FILES))
LOCAL_SRC_FILES := $(filter-out $(enb_rg)/rg_tmr.c,$(LOCAL_SRC_FILES))
# main()
LOCAL_SRC_FILES := $(filter-out $(enb_rg)/rg_tst.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUL) $(LNXIOPTS) $(CCLNXRGOPTS) $(CCrgFLAGS)

include $(BUILD_STATIC_LIBRARY)


#-------------------------------------------------------------#
#Makefile for product TF - script generated.
#-------------------------------------------------------------#

#-------------------------------------------------------------#
#User macros (to be modified)
#-------------------------------------------------------------#

CCysFLAGS=-DTF -DYS -UDEBUG -DLCCTF -DLCYSUITFU -DLCTFU -DLCTFUITFU -DTFU_VER_2 -DNOFILESYS \
          -UTFU_TDD -DRG -DLCYSUICTF -DAPI_MAIN -DLCYSMILYS -DLCLYS -UDEBUGP -DTFU_UPGRADE -DYS_FS \
          -UYS_FS_DBG_L1MSG_DUMP -UYS_FS_DEBUG -ULTEFAPI_DISSECTOR -USM

######################

$(BLD_LNX_UR_OBJS):
	@$(MAKE) -f ur.mak $(CPUL_OBJ)/libur.a COPTS=$(LNX_CFLAG_CPUL) \
	LOPTS='$(LNXLOPTS)' POPTS='$(CCLNXTFOPTS)' IOPTS='$(LNXIOPTS)' VS_DIR='$(UR_DIR)' IN_DIR='$(UR_DIR)' \
	OUT_DIR='$(CPUL_OBJ)' OBJ='$(OBJ)' CC='$(CC) -c' LL='$(LL)' CM_INC='$(CM_INC)' SRC="c"

# COPTS=$(LNX_CFLAG_CPUL)
# LOPTS='$(LNXLOPTS)' [no]
# POPTS='$(CCLNXTFOPTS)'
# IOPTS='$(LNXIOPTS)'

#	$(CC) -c $(COPTS) $(IOPTS) $(POPTS) $(CCysFLAGS) $(IN_DIR)/ur_l1cl.c -o \

###################### libur ######################
include $(CLEAR_VARS)

LOCAL_MODULE := libur

enb_ur := lteclbrcm

LOCAL_SRC_FILES += $(patsubst $(LOCAL_PATH)/%,%,$(wildcard $(LOCAL_PATH)/$(enb_ur)/*.c))
LOCAL_SRC_FILES := $(filter-out $(enb_ur)/ur_stub.c,$(LOCAL_SRC_FILES))

#LOCAL_C_INCLUDES += $(l1_includes)

ifeq ($(mod_stack_preproc),true)
LOCAL_C_PREPROC_FLAG := true
endif

LOCAL_NO_DEFAULT_COMPILER_FLAGS := true
LOCAL_CFLAGS := $(LNX_CFLAG_CPUL) $(LNXIOPTS) $(CCLNXTFOPTS) $(CCysFLAGS)

include $(BUILD_STATIC_LIBRARY)
