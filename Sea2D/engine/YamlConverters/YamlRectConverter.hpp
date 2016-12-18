//
//  YamlRectConverter.hpp
//  Sea2D
//
//  Created by Jibran Syed on 5/9/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef YamlRectConverter_h
#define YamlRectConverter_h

#include <yaml-cpp/yaml.h>
#include "engine/DataTypes/Rect.hpp"

namespace YAML
{
    template<>
    struct convert<sea2d::Rect>
    {
        static Node encode(const sea2d::Rect& rhs)
        {
            Node node;
            
            node.push_back(rhs.origin.x());
            node.push_back(rhs.origin.y());
            node.push_back(rhs.width);
            node.push_back(rhs.height);
            
            return node;
        }
        
        static bool decode(const Node& node, sea2d::Rect& rhs)
        {
            if(!node.IsSequence() || node.size() != 4)
            {
                return false;
            }
            
            rhs.origin.x() = node[0].as<float>();
            rhs.origin.y() = node[1].as<float>();
            rhs.width = node[2].as<float>();
            rhs.height = node[3].as<float>();
            
            return true;
        }
    };
}
#endif /* YamlRectConverter_h */
