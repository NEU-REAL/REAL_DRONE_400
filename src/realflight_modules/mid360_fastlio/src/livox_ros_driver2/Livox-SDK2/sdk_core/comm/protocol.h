//
// The MIT License (MIT)
//
// Copyright (c) 2022 Livox. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#ifndef COMM_PROTOCOL_H_
#define COMM_PROTOCOL_H_

#include <stdint.h>

namespace livox {
namespace lidar {

typedef struct CommPacket CommPacket;

typedef int (*RequestPackCb)(CommPacket *packet);

typedef enum { kRequestPack, kAckPack, kMsgPack } PacketType;

typedef enum { kLidarSdk, kRsvd1, kProtocolUndef } ProtocolType;

typedef enum { kNoNeed, kNeedAck, kDelayAck } NeedAckType;

typedef enum { kParseSuccess, kParseFail } ParseResult;

typedef struct LogCommPacket {
  uint8_t packet_type;
  uint8_t protocol;
  uint8_t protocol_version;
  uint8_t cmd_set;
  uint32_t cmd_code;
  uint32_t sender;
  uint32_t sub_sender;
  uint32_t receiver;
  uint32_t sub_receiver;
  uint32_t seq_num;
  uint8_t *data;
  uint16_t data_len;
  uint32_t padding;
} LogCommPacket;

typedef struct CommPacket {
  uint8_t protocol;
  uint8_t version;
  uint32_t seq_num;
  uint16_t cmd_id;
  uint8_t cmd_type;
  uint8_t sender_type;
  uint8_t* data;
  uint16_t data_len;
} CommPacket;

class Protocol {
 public:
  virtual ~Protocol(){};

  virtual bool ParsePacket(uint8_t *i_buf, uint32_t i_len, CommPacket *o_packet) = 0;

  virtual int32_t Pack(uint8_t *o_buf, uint32_t o_buf_size, uint32_t *o_len, const CommPacket &i_packet) = 0;

  virtual uint32_t GetPreambleLen() = 0;

  virtual uint32_t GetPacketWrapperLen() = 0;

  virtual uint32_t GetPacketLen(uint8_t *buf) = 0;

  virtual bool CheckPreamble(uint8_t *buf, uint32_t buf_size) = 0;

};

} // namespace lidar
}  // namespace livox
#endif  // COMM_PROTOCOL_H_
