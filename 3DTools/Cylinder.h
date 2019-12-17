#pragma once
#include "renderable.h"
#include "../cgtools/point.h"
#include "Group.h"
namespace DDD {
	class Cylinder :public Group {
        double radius;
        double height;
        std::shared_ptr<AMaterial> material;
        friend class renderable;
        static const int CLASSID = 4;
        Cylinder(std::string serialized);
        void makeChildren();
    public:
		Cylinder(cgtools::point position, double radius, double height, std::shared_ptr<AMaterial> mat);
        std::string serialize()const override;
        void load(std::string serialized) override;
        renderable* clone() const override;
        size_t size()const noexcept override;
    };

}

