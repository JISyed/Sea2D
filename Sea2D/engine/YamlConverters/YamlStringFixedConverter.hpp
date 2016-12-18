//
//  YamlStringFixedConverter.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/9/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef YamlStringFixedConverter_h
#define YamlStringFixedConverter_h

#include <yaml-cpp/yaml.h>
#include "engine/DataTypes/StringFixed.hpp"
#include <string>

namespace YAML
{
    template<>
    struct convert<sea2d::StringFixed>
    {
        static Node encode(const sea2d::StringFixed& rhs)
        {
            Node node;
            
            std::string outStr(rhs.GetCString());
            node.push_back(outStr);
            
            return node;
        }
        
        static bool decode(const Node& node, sea2d::StringFixed& rhs)
        {
            if(!node.IsScalar())
            {
                return false;
            }
            
            std::string inStr = node.as<std::string>();
            rhs.Set(inStr.c_str());
            
            return true;
        }
    };
}
#endif /* YamlStringFixedConverter_h */
