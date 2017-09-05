/*
 * Copyright (C) 2017  Yannick Jadoul
 *
 * This file is part of Parselmouth.
 *
 * Parselmouth is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Parselmouth is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Parselmouth.  If not, see <http://www.gnu.org/licenses/>
 */

#include "Parselmouth.h"

#include <pybind11/numpy.h>

namespace py = pybind11;
using namespace py::literals;

namespace parselmouth {

void Binding<Sampled>::init()
{
	def_readonly("ymin", &structSampledXY::ymin);

	def_readonly("ymax", &structSampledXY::ymax);

	def_property_readonly("yrange", [](SampledXY self) { return std::make_pair(self->ymin, self->ymax); });

	def_readonly("ny", &structSampledXY::ny);

	def_readonly("y1", &structSampledXY::y1);

	def_readonly("dy", &structSampledXY::dy);

	def("ys",
	    [](SampledXY self) {
		    py::array_t<double> ys(self->ny);
		    auto unchecked = ys.mutable_unchecked<1>();
		    for (auto i = 0; i < self->ny; ++i) {
			    unchecked(i) = self->y1 + i * self->dy;
		    }
		    return ys;
	    });
}

} // namespace parselmouth
