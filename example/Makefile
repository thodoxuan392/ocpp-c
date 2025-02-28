GCC := gcc
OCPP_DIR := ..
LOGGER_DIR := ./logger
JSMN_DIR := ../../jsmn

OPTION := -DJSMN_STATIC

OCPP_INCLUDE_DIR := \
	-I $(OCPP_DIR)/include	\
	-I $(OCPP_DIR)/include/message \
	-I $(JSMN_DIR) \
	-I $(LOGGER_DIR)


OCPP_SOURCE_FILE := \
	$(OCPP_DIR)/src/Ocpp.c	\
	$(OCPP_DIR)/src/OcppJson.c	\
	$(OCPP_DIR)/src/message/OcppAuthorize.c	\
	$(OCPP_DIR)/src/message/OcppBootNotification.c	\
	$(OCPP_DIR)/src/message/OcppCancelReservation.c	\
	$(OCPP_DIR)/src/message/OcppChangeAvailability.c	\
	$(OCPP_DIR)/src/message/OcppChangeConfiguration.c	\
	$(OCPP_DIR)/src/message/OcppClearCache.c	\
	$(OCPP_DIR)/src/message/OcppClearChargingProfile.c	\
	$(OCPP_DIR)/src/message/OcppDataTransfer.c	\
	$(OCPP_DIR)/src/message/OcppDiagnosticStatusNotification.c	\
	$(OCPP_DIR)/src/message/OcppFirmwareStatusNotification.c	\
	$(OCPP_DIR)/src/message/OcppGetCompositeSchedule.c	\
	$(OCPP_DIR)/src/message/OcppGetConfiguration.c	\
	$(OCPP_DIR)/src/message/OcppGetDiagnostics.c	\
	$(OCPP_DIR)/src/message/OcppGetLocalListVersion.c	\
	$(OCPP_DIR)/src/message/OcppHeartBeat.c	\
	$(OCPP_DIR)/src/message/OcppMeterValue.c	\
	$(OCPP_DIR)/src/message/OcppRemoteStartTransaction.c	\
	$(OCPP_DIR)/src/message/OcppRemoteStopTransaction.c	\
	$(OCPP_DIR)/src/message/OcppReserveNow.c	\
	$(OCPP_DIR)/src/message/OcppReset.c	\
	$(OCPP_DIR)/src/message/OcppSendLocalList.c	\
	$(OCPP_DIR)/src/message/OcppSetChargingProfile.c	\
	$(OCPP_DIR)/src/message/OcppStartTransaction.c	\
	$(OCPP_DIR)/src/message/OcppStatusNotification.c	\
	$(OCPP_DIR)/src/message/OcppStopTransaction.c	\
	$(OCPP_DIR)/src/message/OcppTriggerMessage.c	\
	$(OCPP_DIR)/src/message/OcppUnlockConnector.c	\
	$(OCPP_DIR)/src/message/OcppUpdateFirmware.c	\
	$(LOGGER_DIR)/utils_logger.c	\


build_msg:
	$(GCC) $(OCPP_INCLUDE_DIR) -I $(OCPP_DIR)/example/build_message $(OCPP_SOURCE_FILE) $(OCPP_DIR)/example/build_message/main.c $(OPTION) -o $(OCPP_DIR)/example/build_message/main



parse_msg:
	$(GCC) $(OCPP_INCLUDE_DIR) -I $(OCPP_DIR)/example/parse_message $(OCPP_SOURCE_FILE) $(OCPP_DIR)/example/parse_message/main.c $(OPTION) -o $(OCPP_DIR)/example/parse_message/main