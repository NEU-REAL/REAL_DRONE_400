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

#ifndef LIVOX_PARSE_CFG_FILE_H_
#define LIVOX_PARSE_CFG_FILE_H_

#include "livox_lidar_def.h"

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"

#include "comm/define.h"

#include <iostream>
#include <string>
#include <memory>
#include <vector>

namespace livox {
namespace lidar {

class ParseCfgFile {
 public:
  explicit ParseCfgFile(const std::string& path);  
  bool Parse(std::shared_ptr<std::vector<LivoxLidarCfg>>& lidars_cfg_ptr,
             std::shared_ptr<std::vector<LivoxLidarCfg>>& custom_lidars_cfg_ptr,
             std::shared_ptr<LivoxLidarLoggerCfg>& lidar_logger_cfg_ptr,
             std::shared_ptr<LivoxLidarSdkFrameworkCfg>& sdk_framework_cfg_ptr
             );
 private:
  bool ParseLidarCfg(const rapidjson::Value &object,
                     const uint8_t& device_type,
                     std::shared_ptr<std::vector<LivoxLidarCfg>>& lidars_cfg_ptr,
                     std::shared_ptr<std::vector<LivoxLidarCfg>>& custom_lidars_cfg_ptr);
  bool ParseNewLidarCfg(const rapidjson::Value &object,
                     const uint8_t& device_type,
                     std::shared_ptr<std::vector<LivoxLidarCfg>>& lidars_cfg_ptr,
                     std::shared_ptr<std::vector<LivoxLidarCfg>>& custom_lidars_cfg_ptr);
  bool ParseOldLidarCfg(const rapidjson::Value &object,
                        const uint8_t& device_type,
                        std::shared_ptr<std::vector<LivoxLidarCfg>>& lidars_cfg_ptr);
  bool ParseTypeLidarCfg(const rapidjson::Value &object, const rapidjson::Value &host_net_info_object, const uint8_t& device_type, LivoxLidarCfg& lidar_cfg);
  bool ParseLidarNetInfo(const rapidjson::Value &object, LivoxLidarNetInfo& lidar_net_info);
  bool ParseHostNetInfo(const rapidjson::Value &host_net_info_object, HostNetInfo& host_net_info);
  bool ParseGeneralCfgInfo(const rapidjson::Value &object, GeneralCfgInfo& general_cfg_info);
 private:
  const std::string path_;
};

} // namesace lidar
} // namespace livox

#endif // LIVOX_PARSE_CFG_FILE_H_

