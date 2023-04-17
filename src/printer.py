# Copyright (C) 2018-2023 Ton Chanh Le

# SLING is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# SLING is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with SLING. If not, see <https://www.gnu.org/licenses/>.

class Printer(object):
    @classmethod
    def str_of(self, obj):
        method_name = 'str_of_' + type(obj).__name__
        gen_str = getattr(self, method_name, str)
        return gen_str(obj)

    @classmethod
    def str_of_list(self, obj):
        elems = map(lambda e: self.str_of(e), obj)
        if (any(hasattr(e, '__dict__') for e in obj) and
           any(len(e) > 80 for e in elems)):
            sep = ',\n\n'
        else:
            sep = ', '
        return '[' + (sep.join(elems)) + ']'

    @classmethod
    def str_of_tuple(self, obj):
        elems = map(lambda e: self.str_of(e), list(obj))
        return '(' + (', '.join(elems)) + ')'

    @classmethod
    def str_of_dict(self, obj):
        elems = []
        for k in obj:
            elems.append(self.str_of(k) + ': ' + self.str_of((obj[k])))
        return '{\n' + ('\n'.join(elems)) + '}'
