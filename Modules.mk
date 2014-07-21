LOCAL_PATH := $(call my-dir)

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

#	$(CC)  -o$(OUT_DIR)/wr_emm_eom.$(OBJ) -I$(SS_DIR) $(COPTS) $(IOPTS) $(POPTS) $(CCwrFLAGS) \

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

# wr_ex_ms
#LOCAL_CFLAGS += -ULCWR -DRG  -DLWLCWR  -DLWLCLWR   -DLCLWR -DSM
# wr_smm_enbapp_rsys
#LOCAL_CFLAGS += -DLWLCSMMILWR  -DLWLCSWR -DLWLCWRMILWR -DSM -UPTSMMILWR
# wr_smm_mac
#LOCAL_CFLAGS += -DLCRGMILRG  -DLCLRG -DLCSMMILRG
# wr_smm_x2ap
#LOCAL_CFLAGS += -DLCSMMILCZ -DLCLCZ -DCZ_ENB
# wr_smm_rlc
#LOCAL_CFLAGS += -DLCKWMILKW -DLCPJMILPJ -DLCLKW
# wr_smm_rrc
#LOCAL_CFLAGS += -DLCSMNHMILNH -DLCLNH

#LOCAL_CFLAGS := $(sort $(LOCAL_CFLAGS))

include $(BUILD_STATIC_LIBRARY)
