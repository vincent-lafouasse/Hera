//
// Created by vincent lafouasse on 29/03/2025.
//

#ifndef STEREOINTEGRATOR_HPP
#define STEREOINTEGRATOR_HPP

#include <array>

template <typename FloatType>
class StereoIntegrator {
   public:
    StereoIntegrator(FloatType inertia_weight, FloatType forward_weight)
        : inertia_weight_(inertia_weight), forward_weight_(forward_weight) {}
    ~StereoIntegrator() = default;

    void setTarget(FloatType target) { this->target_ = target; }

    FloatType get(std::size_t channel) {
        memory_[channel] =
            inertia_weight_ * memory_[channel] + forward_weight_ * target_;
        return memory_[channel];
    }

   private:
    FloatType target_;
    FloatType inertia_weight_;
    FloatType forward_weight_;
    std::array<FloatType, 2> memory_;
};

#endif  // STEREOINTEGRATOR_HPP
