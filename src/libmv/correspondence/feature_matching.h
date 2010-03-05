// Copyright (c) 2009 libmv authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.


#ifndef LIBMV_CORRESPONDENCE_FEATURE_MATCHING_H_
#define LIBMV_CORRESPONDENCE_FEATURE_MATCHING_H_

#include "libmv/base/vector.h"
#include "libmv/correspondence/kdtree.h"
#include "libmv/correspondence/feature.h"
#include "libmv/correspondence/matches.h"
#include "libmv/descriptor/descriptor.h"
#include "libmv/descriptor/vector_descriptor.h"

using namespace libmv;

/// Define the description of a feature described by :
/// A PointFeature (x,y,scale,orientation),
/// And a descriptor (a vector of floats).
struct KeypointFeature : public ::PointFeature {
  descriptor::VecfDescriptor descriptor;
  // Match kdtree traits: with this, the Feature can act as a kdtree point.
  float operator[](int i) const { return descriptor.coords(i); }
};

/// FeatureSet : Store an array of KeypointFeature and a Kdtree of the descriptor.
struct FeatureSet {
  vector<KeypointFeature> features;
  KdTree<float> tree;

  /// return a float * containing the descriptor data.
  /// Must be deleted with []
  static float *FeatureSetDescriptorsToContiguousArray
    ( const FeatureSet & featureSet );

};

// Compute candidate matches between 2 sets of features.  Two features a and b
// are a candidate match if a is the nearest neighbor of b and b is the nearest
// neighbor of a.
void FindCandidateMatches(const FeatureSet &left,
                          const FeatureSet &right,
                          Matches *matches);


#endif //LIBMV_CORRESPONDENCE_FEATURE_MATCHING_H_