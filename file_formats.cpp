/*
 * Platformer Game Engine by Wohlstand, a free platform for game making
 * Copyright (c) 2014-2020 Vitaly Novichkov <admin@wohlnet.ru>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pge_file_lib_sys.h"
#include "pge_file_lib_private.h"

#include "file_formats.h"


PGESTRING FileFormats::removeQuotes(PGESTRING str)
{
    PGESTRING target = str;
#ifdef PGE_FILES_QT
    if(target.isEmpty())
        return target;
    if(target[0] == QChar('\"'))
        target.remove(0, 1);
    if((!target.isEmpty()) && (target[target.size() - 1] == QChar('\"')))
        target.remove(target.size() - 1, 1);
#else
    if(target.empty())
        return target;
    if(target[0] == '\"')
        target.erase(target.begin() + 0);
    if((!target.empty()) && (target[target.size() - 1] == '\"'))
        target.erase(target.begin() + (std::string::difference_type)target.size() - 1);
#endif
    return target;
}

PGESTRING FileFormats::getErrorString(FileFormats::ErrorCodes errCode)
{
    switch(errCode)
    {
    case Success:
        return "";
    case ERROR_NotExist:
        return "File not exist";
    case ERROR_AccessDenied:
        return "Access denied";
    case ERROR_InvalidSyntax:
        return "Invalid file format";
    case ERROR_PGEX_SectionNotClosed:
        return "PGE-X Section is not closed";
    case ERROR_PGEX_InvalidSyntax:
        return "PGE-X Invalid data entry syntax";
    case ERROR_PGEX_InvalidDataType:
        return "PGE-X Invalid data type";
    }
    return "Unknown error";
}

/***************************************************************************/
CrashData::CrashData() : used(false), untitled(false), modifyed(false), strictModeSMBX64(false), fmtID(0), fmtVer(64) {}

CrashData::CrashData(const CrashData &_cd)
{
    this->used = _cd.used;
    this->untitled = _cd.untitled;
    this->modifyed = _cd.modifyed;
    this->strictModeSMBX64 = _cd.strictModeSMBX64;
    this->fmtID   = _cd.fmtID;
    this->fmtVer  = _cd.fmtVer;
    this->fullPath = _cd.fullPath;
    this->filename = _cd.filename;
    this->path = _cd.path;
}

void CrashData::reset()
{
    used = false;
    untitled = false;
    modifyed = false;
    strictModeSMBX64 = false;
    fmtID   = 0;
    fmtVer  = 0;
    fullPath.clear();
    filename.clear();
    path.clear();
}
