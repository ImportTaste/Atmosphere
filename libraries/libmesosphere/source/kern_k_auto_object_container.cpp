/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <mesosphere.hpp>

namespace ams::kern {


    Result KAutoObjectWithListContainer::Register(KAutoObjectWithList *obj) {
        KScopedLightLock lk(this->lock);

        this->object_list.insert(*obj);

        return ResultSuccess();
    }

    Result KAutoObjectWithListContainer::Unregister(KAutoObjectWithList *obj) {
        KScopedLightLock lk(this->lock);

        this->object_list.erase(this->object_list.iterator_to(*obj));

        return ams::svc::ResultNotFound();
    }

    size_t KAutoObjectWithListContainer::GetOwnedCount(KProcess *owner) {
        KScopedLightLock lk(this->lock);

        size_t count = 0;

        for (auto &obj : this->object_list) {
            if (obj.GetOwner() == owner) {
                count++;
            }
        }

        return count;
    }

}