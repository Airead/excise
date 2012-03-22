#!/bin/sh

echo ./all_basic_data_deliver_client Boolean False
./all_basic_data_deliver_client Boolean False
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Byte f
./all_basic_data_deliver_client Byte f
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Double 3.2
./all_basic_data_deliver_client Double 3.2
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Int16 4
./all_basic_data_deliver_client Int16 4
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Int32 4
./all_basic_data_deliver_client Int32 4
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Int64 2
./all_basic_data_deliver_client Int64 2
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Objectpath "/object"
./all_basic_data_deliver_client Objectpath "/object"
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Signature i
./all_basic_data_deliver_client Signature i
echo -e "=================================\n"
echo ./all_basic_data_deliver_client String String
./all_basic_data_deliver_client String String
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Uint32 99
./all_basic_data_deliver_client Uint32 99
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Uint64 33
./all_basic_data_deliver_client Uint64 33
echo -e "=================================\n"
echo ./all_basic_data_deliver_client Uint16 35
./all_basic_data_deliver_client Uint16 35
echo -e "=================================\n"
