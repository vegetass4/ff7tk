/****************************************************************************/
//    copyright 2019-2020 Chris Rizzitello <sithlord48@gmail.com>           //
//                                                                          //
//    This file is part of FF7tk                                            //
//                                                                          //
//    FF7tk is free software: you can redistribute it and/or modify         //
//    it under the terms of the GNU General Public License as published by  //
//    the Free Software Foundation, either version 3 of the License, or     //
//    (at your option) any later version.                                   //
//                                                                          //
//    FF7tk is distributed in the hope that it will be useful,              //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of        //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
//    GNU General Public License for more details.                          //
/****************************************************************************/
#include "FF7SaveInfo.h"

#include <QByteArrayList>
#include <QQmlEngine>

struct FF7SaveInfo::FF7SaveInfoPrivate {
    static const int _slotSize = 0x10F4;
    /*~~~~~~~~~~~~~~~~~~PC Save File ~~~~~~~~~~~~*/
    static const int PC_FILE_SIZE = 0xFE55;
    static const int PC_FILE_HEADER_SIZE = 0x09;
    inline static const QString PC_FILE_DESCRIPTION = tr("PC Save File");
    inline static const QStringList PC_VALID_EXTENSIONS { QStringLiteral("*.ff7") };
    inline static const QRegExp PC_VALID_NAME_REGEX = QRegExp(QStringLiteral("save0[0-9].ff7"));
    inline static const QByteArray PC_FILE_ID = QByteArray::fromRawData("\x71\x73\x27\x06", 4);
    /*~~~~~~~~~~~~~~~~~~ Switch Save File ~~~~~~~~~~~~~*/
    static const int SWITCH_FILE_SIZE = PC_FILE_SIZE;
    static const int SWITCH_FILE_HEADER_SIZE = PC_FILE_HEADER_SIZE;
    inline static const QString SWITCH_FILE_DESCRIPTION = tr("Switch Save File");
    inline static const QStringList SWITCH_VALID_EXTENSIONS {QStringLiteral("ff7slot*")};
    inline static const QRegExp SWITCH_VALID_NAME_REGEX = QRegExp(QStringLiteral("ff7slot[0-9]"));
    inline static const QByteArray SWITCH_FILE_ID = PC_FILE_ID;
    /*~~~~~~~~~~~~~~~~~~ Psx save file ~~~~~~~~~~~~~~~~*/
    static const int PSX_FILE_SIZE = 0x2000;
    static const int PSX_SLOT_HEADER_SIZE = 0x0200;
    static const int PSX_SLOT_FOOTER_SIZE = 0x0D0C;
    inline static const QString PSX_FILE_DESCRIPTION = tr("PSX Save File");
    inline static const QStringList PSX_VALID_EXTENSIONS { QStringLiteral("BASCUS-94163FF7-S*"),
        QStringLiteral("BESCES-00867FF7-S*"), QStringLiteral("BESCES-00868FF7-S*"),
        QStringLiteral("BESCES-00869FF7-S*"), QStringLiteral("BESCES-00900FF7-S*"),
        QStringLiteral("BISLPS-00700FF7-S*"), QStringLiteral("BISLPS-01057FF7-S*")};
    inline static const QRegExp PSX_VALID_NAME_REGEX = QRegExp(QStringLiteral("(BASCUS|BESCES|BISLPS)-\\d{5}FF7-S([1][0-5]|0[1-9])"));
    inline static const QByteArray PSX_FILE_ID = QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60", 16);
    //BELOW 1/2 HEADER DATA FOR EACH PSX SAVE SLOT, (NOTE: last 256 bytes are 0x00, no region data in this section)
    inline static const QByteArrayList PSX_SLOT_HEADER = {
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x50\x81\x5E\x82\x4F\x82\x58\x81\x46\x82\x54\x82\x4F\x00\x00\x00\x00\x62\x75\x31\x30\x3A\x00\x00\x00\x62\x75\x30\x30\x3A\x00\x00\x00\xA0\x3B\x1D\x80\x8C\x3C\x1D\x80\x00\x3F\x1D\x80\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1D\x57\xDD\x3E\xBA\x42\xB7\x5E\x53\x5A\x38\x2E\xF8\x1D\xF3\x39\xEE\x59\xEC\x71\xB3\x1D\x8E\x39\x87\x7D\x08\x31\xFF\x7F\xFF\x15\x21\x76\xF3\xFF\xFF\xFF\xDF\x5D\x32\x63\x66\xDA\xDD\xFD\xDF\x8A\x66\x77\x77\x56\xDD\xFD\x4F\x71\x68\x13\x7B\x22\xD5\xFD\x55\x47\x11\x81\x3E\x22\xA2\xFD\xDF\x15\x11\xB3\x5E\x72\x52\xF8\xAF\x32\x31\x2B\x61\xB2\x77\xFD\x8F\x37\x62\x16\x61\x73\x67\xF8\xCF\x67\xBB\x32\xB8\x76\xBB\xFD\xBF\x76\xEB\xB3\xEC\xB7\xCB\xF8\x7F\xB7\x1B\x31\x11\xE7\xD7\xFD\x7F\x5B\x38\x31\x11\xEB\xD8\xFD\xBF\xAA\xB7\x11\x31\xEB\xDC\xFD\xAF\xDD\xB8\x18\xB3\xCE\xDE\xFD\xDF\xDD\xBA\xED\xCC\xCC\xDE\xFD\xFF\xFF\xBF\xEF\x5C\xEC\xEE\xFF", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x51\x81\x5E\x82\x58\x82\x58\x81\x46\x82\x54\x82\x58\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x50\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1B\x63\x5A\x42\x72\x62\x11\x4A\xB6\x2D\xEC\x69\x56\x21\x90\x31\x87\x7D\x8C\x39\x29\x2D\x0D\x1D\xE8\x1C\xC7\x14\xFF\x7F\xFF\xFF\x1F\x44\xAA\xFF\xFF\xFF\x9F\x99\x36\xC4\xED\x9A\x99\xF9\x9F\x99\xFA\x72\xC7\x9C\x99\xF9\x9F\x99\xF1\x51\x75\xAC\x99\xF9\x9F\x39\xFF\x84\x77\xDC\x94\xF9\x9F\x39\x82\x8B\x57\xCC\x6A\xF9\x9F\x89\xCC\x21\x75\xDD\xEC\xFB\x9F\x49\x82\x11\xC7\xEE\xCD\xDE\x9F\x89\xBC\xBD\xEC\xEE\x7E\xDC\x9F\xB9\x38\xD4\xEE\xEE\x7E\xC7\x9F\xDA\x85\x52\xED\xEE\xCE\xC7\xAF\xED\xDC\xCC\xEE\xEE\xCE\x77\xCF\xED\xBB\xED\xEE\xEE\xCE\x57\x84\xEB\xBB\xEE\xEE\xEE\x7C\x57\x58\xD8\xEE\xEE\xCE\x77\x7C\x25\x85\xD8\xCE\xC7\x7C\x75\x5C\x22", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x52\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x51\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x51\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1C\x5F\x9B\x4A\x95\x5E\x56\x4A\xBA\x3D\x11\x4E\xD4\x39\xEC\x69\xA9\x79\xAF\x41\x74\x21\x86\x7D\x4F\x25\xEF\x18\xFF\x7F\xFF\xFF\x1F\x44\xF1\xFF\xFF\xFF\x8F\x88\x88\x27\xA2\xC8\xCC\xFC\x3F\x77\xA7\x2B\x21\xC4\xCC\xFC\x1F\xE7\x7E\xED\xFF\x61\xCC\xFC\x1F\xAB\xEE\xED\x1B\x21\xC6\xFC\x2F\xCB\x2A\x1F\x7B\x25\x87\xFC\xBF\xCD\x16\x1F\xBB\x7B\x74\xF8\xDF\xCD\xF6\x4F\xBE\xBB\x74\xF8\x8F\xCD\xA6\xD1\xEE\xBE\xED\xF6\xCF\xC8\x8B\x11\xD8\xEE\xE7\x15\xCF\xCC\xFE\xF2\xDF\xEB\xED\x5E\xCF\xCC\x1E\xF1\x2F\xEB\xBE\xBB\xCF\xCC\xBE\xF1\xB1\xBE\xEE\x55\xCF\xEC\xEB\x2B\xED\xBE\xEE\xF4\xCF\xEC\xBB\xBE\xB2\xBE\xEE\x1A\xFF\x1F\xBE\xFE\x51\xEE\xEE\x34", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x53\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x51\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x52\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x9D\x73\x5B\x6B\xF9\x5E\xF6\x6A\xD5\x62\x77\x52\x2E\x6E\x31\x4A\x76\x18\xC9\x75\x6A\x49\x77\x31\x86\x7D\x09\x31\xFF\x7F\xFF\xFF\x7F\xA8\xFF\xFF\xFF\xFF\xDF\x77\xB7\xA6\xDD\xDD\xDD\xFD\xAF\x68\xEC\xAC\x7D\xA7\xAF\xFA\xB7\x3C\xE8\xBE\x7D\x5F\x7F\xFF\xEB\xEE\xEE\xEE\xC9\xF6\x1F\x55\xC6\xEE\x8B\xEB\x6C\x13\xF1\xFF\xBF\xEE\xF8\xBE\xFE\x1F\x21\x5A\xDF\xBE\xFE\x51\xBE\x47\x55\x24\x9F\xEB\x38\x6C\xF3\xFF\xFF\x31\x8F\xE8\x6E\x36\xF2\x6F\x11\xF3\xF8\x81\x22\x22\xFF\x1F\x62\x36\x18\x56\xFF\xFF\x21\x12\xF1\x1F\x8F\xF5\xF6\x21\x12\xFF\xFF\xFF\x5F\xF1\x11\x13\xFF\xFF\xF1\xFF\x14\x33\x33\xF1\x1F\x1F\xF3\xFF\x13\xF3\x16\xFF\x3F\x31\xFF\x1F", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x54\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x52\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x53\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x1E\x2E\x36\x3E\xD7\x2D\x5C\x21\xCC\x65\xB0\x49\x8C\x10\xAE\x51\x9C\x73\x87\x7D\x35\x1D\x11\x29\x0D\x25\xB0\x14\xFF\x7F\xFF\x99\x99\xCE\x89\xCE\xEE\xBC\xAF\xEC\xCE\xEE\xEC\xC7\xBE\x4B\xAF\xAA\xEE\xE7\x7E\xE7\x4B\xE4\xAF\xDC\xCD\x77\x7E\xEE\xEE\xEE\xCF\xEE\xEE\x7E\xEE\xBE\xBB\xBE\xAF\xAA\xDC\xEE\xBE\x44\x7D\x3B\xAF\xAA\xAA\xBB\x11\x14\x7D\x13\xAF\xAA\xEA\x44\x43\x11\x73\x11\xAF\xAA\xD5\xDE\x39\x11\xD4\x33\xAF\x5A\xCC\x14\x43\xEE\xDB\x95\xAF\xDA\x47\x41\x4B\x41\xDE\xFA\xAF\x6A\x11\xB1\xE8\xBE\x8E\xFA\xAF\xAA\x13\x64\xA2\xC5\x2D\xFA\xAF\xAA\x35\x83\xAC\xAA\x85\xFA\xAF\xAA\xAA\x8A\xAC\xAA\xEA\xFA\xFF\xFF\xFF\x9F\xF9\xFF\xE9\xF5", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x55\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x52\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x54\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x3C\x5B\x3E\x4F\xDD\x36\x99\x46\x1C\x22\x30\x62\x8D\x31\x32\x46\xD0\x35\xCB\x59\xA8\x79\x86\x7D\x71\x21\x4B\x29\xFF\x7F\xFF\xFF\xFF\x46\x64\xF6\xFF\xFF\xCF\xCC\x6C\x21\x32\x64\xCC\xFC\xCF\xCC\x16\xFF\xFF\x22\xC6\xFC\xCF\xAC\x23\xF1\x2F\x23\x63\xFC\xCF\x84\xDD\x88\x34\x54\x35\xFA\xAF\x84\xEE\x44\xD8\x49\x55\xF6\xAF\xEE\xED\x48\xE8\x18\x54\xF4\xCF\xDA\x77\xED\xEE\x8E\x58\xF5\xCF\x8C\xDD\xDE\x44\x88\xD8\xF6\xCF\x8C\x22\x44\x31\x43\xAA\xFC\xCF\xAC\x44\xF1\x52\x45\xAA\xFC\xCF\xAC\x48\x48\xD5\xDD\xA8\xFC\xAF\x48\xF2\x58\x7D\x77\xEE\xF7\xAF\xC4\x46\x42\x77\xEE\xEE\xF7\xCF\xCC\x8A\xE8\xEE\xEE\x7E\xA7\xFF\xAF\xEE\xEE\x77\xEE\x7E\xA8", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x56\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x52\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x55\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x7D\x6B\x18\x63\xDC\x4A\x77\x4A\x51\x5E\x32\x46\xCC\x65\xA9\x75\x86\x7D\x8D\x31\x69\x49\x29\x25\x28\x25\xE7\x1C\xFF\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x8F\x88\xA8\x65\xA6\xAC\x88\xF8\x8F\x88\xDA\xAA\xEE\xCC\x88\xF8\x8F\xA8\xAE\x66\xEA\xAA\xAA\xF8\x8F\xD8\xAE\x6A\x46\xEA\xAE\xF8\x8F\xE8\xEE\xAC\xF3\xE4\xAC\xF8\x8F\xEA\xAA\xA6\x16\xE2\x66\xFA\x8F\xEA\x33\x41\x2C\xE6\x22\xFA\x8F\xEA\x31\x1F\xF2\xA6\x22\xFA\x8F\xEA\x34\xF1\xFF\x42\x16\xF5\x8F\xEA\x3A\xFF\x1F\xDA\x2A\xF2\x8F\xEA\x4E\x22\x11\x2E\x6C\xF6\x8F\xEA\xEE\x3E\x1F\xFE\xAE\x66\x8F\xE8\xEE\x1A\xFF\xEE\xAE\xAA\x8F\xEA\xEE\x14\xFF\xE6\xEE\xAC\xFF\xE5\x6E\x13\xFF\xC1\xEE\xCE", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x57\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x52\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x56\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xD8\x56\x3D\x46\xDC\x4A\xDC\x3D\x0E\x52\xB5\x39\xC9\x71\xAE\x35\x87\x7D\x17\x21\x6A\x35\xF3\x20\xEF\x1C\xE8\x1C\xFF\x7F\xFF\xFF\xFF\x1F\x11\xFF\xFF\xFF\x9F\x99\xB7\x8B\xEB\xBE\x99\xF9\x9F\x79\xEB\x18\x81\xEE\x9B\xF9\x9F\xB7\xEE\x8E\xF5\xE8\xBE\xF9\x7F\xEB\xEE\xEE\x5B\xE8\xEE\xF9\xBF\xDD\xDC\xDD\xEE\xEE\xEE\xFB\xBF\xCD\xAA\x4A\xEC\xEC\xEE\xFB\xBF\xCD\xEE\xAC\xEA\xED\xEE\xFB\xE1\xDD\xEB\x4A\xEC\xEC\xEE\xFB\xEE\x8E\xEB\xDE\xDE\xEE\xEE\xFB\xED\x6E\xEB\xF3\x33\xEE\xEE\xFE\xDD\x8C\xCE\xFF\x3F\xEE\xEE\xFE\xCC\x8A\xCE\x36\xE6\xDE\xEE\xFE\xAA\x64\xAE\xA4\xDD\xCD\xBE\xFE\x46\x62\xAD\x12\x1F\xC1\xBE\x1C\x24\x64\x44\x44\xAA\xCC\xEE\xCA", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x58\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x52\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x57\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x3E\x4F\xDC\x4E\x13\x42\x52\x4A\xB0\x35\x4D\x29\xB5\x56\xA9\x75\xA8\x14\xA7\x7D\xC7\x29\x89\x4D\xEA\x1C\x66\x1D\xFF\x7F\xFF\xFF\xFF\x44\x44\xFF\xFF\xFF\xAF\xAA\x6C\x55\xD6\xCD\xAA\xFA\xAF\xCA\x35\x53\x65\xDD\xAC\xFA\xAF\x5C\x33\x35\x55\xD6\xAD\xFA\xAF\x35\x53\x33\x35\xD6\xC9\xFA\xAF\x35\x53\x53\x56\x66\xD9\xFA\xAF\x36\x63\x65\x69\x67\xDD\xFA\xAF\x5D\x93\x96\x49\x94\xDD\xFA\xAF\x6D\x65\x67\x21\x61\x6D\xFA\xAF\xDC\x56\x12\x21\x32\xC6\xFA\xAF\xEC\x6D\x12\x31\x32\xAC\xFA\xAF\xBE\xD9\x23\x74\xD3\xAC\xFA\xCF\xEE\xE9\x3D\x32\x9D\xC4\xFA\xEF\xEB\xE8\x6B\xDD\x99\xB7\xFC\xEC\x3E\xE2\xEB\xEE\xEE\x47\xBB\xBE\x13\xBE\xEB\xEB\x4E\x47\xB4", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x4F\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x52\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x4F\x82\x58\x81\x5E\x82\x4F\x82\x4F\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xFC\x52\x7B\x36\x74\x4E\x72\x5E\x15\x32\xF2\x39\x0C\x6E\xC9\x79\xA8\x7D\x9C\x73\x8F\x29\xAD\x35\x86\x7D\x29\x29\xFF\x7F\xFF\xFF\xFF\xAA\xAA\xFF\xFF\xFF\xDF\xDD\x79\x53\xB6\xD8\xDD\xFD\xDF\x9D\x24\x22\x55\x8B\xDD\xFD\xDF\x4D\x21\x22\x22\xB5\xD8\xFD\xDF\x29\x52\x5B\xB5\xBB\x9C\xFD\xDF\x29\x21\x53\x26\xB2\x8B\xFD\xDF\x39\xFF\xFF\x1F\x52\x52\xFD\xDF\x39\xF1\xFF\x1F\x62\x2B\xFD\xDF\x67\xE6\x16\xE3\x5C\x2B\xFD\xDF\xC8\xFF\xF1\x12\x52\x57\xFD\xDF\xCD\xF1\xFF\xF2\x72\x7D\xFD\xDF\xDD\xFC\x1F\x12\x76\x9D\xFD\xDF\x9D\xCE\xFF\x51\xCE\xD9\xFD\xDF\x6D\xEE\x3C\xE5\xEE\x96\xFD\xDA\xC6\xCE\xEE\xEE\xEE\x6C\xA9\x11\xC6\xEE\xCC\xEC\xEE\x6C\x16", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x50\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x52\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x4F\x81\x5E\x82\x50\x82\x50\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xBE\x67\xFB\x52\x79\x3A\x31\x4A\x14\x36\xFF\x7F\x83\x10\xD0\x35\x87\x7D\x19\x6B\x6A\x35\x2A\x25\x27\x35\xE5\x24\xFF\x7F\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x9F\x99\x99\xBB\xBC\x99\x99\xF9\x9F\x99\xB9\xEC\xEE\x9E\x99\xF9\x9F\x99\xCB\xCC\xCE\xBE\x99\xF9\x9F\x99\x2B\x53\x35\xC5\x99\xF9\x9F\x99\x18\x11\x11\x82\x99\xF9\x9F\x99\x14\x11\x11\x83\x99\xF9\x9F\x49\x84\x2B\x82\x5B\x94\xF9\x9F\x89\x22\x12\x33\x53\x9B\xF9\x9F\xB9\x1C\x11\x13\xC2\x9E\xF9\x9F\xE9\x47\x11\x23\xE5\xBE\xF9\x9F\x7B\xC7\x22\x52\xEB\xE7\xF9\xBA\x77\x87\x54\xC5\xB4\x77\xAB\x7B\x77\x8E\xC1\x4C\xE4\x7E\xBD\xEE\xE7\xBE\xE2\x8E\xEB\x7D\xDE\xDE\x7E\xEE\xC8\x8C\xDE\xE7\xEE", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x51\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x53\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x50\x81\x5E\x82\x50\x82\x50\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xBF\x6F\x7C\x6B\x1B\x5B\xBB\x3E\xD7\x4E\x97\x3A\x31\x56\x14\x32\x9C\x73\xED\x59\xD1\x2D\x09\x21\x86\x7D\x8D\x35\xFF\x7F\xFF\xFF\xFF\x99\xF9\xFF\xFF\xFF\xDF\xDD\x5A\x65\x76\xDA\xDD\xFD\xDF\xAD\x55\x66\x68\xA5\xDD\xFD\xDF\x5D\x63\x86\x66\x54\xDD\xFD\xDF\x3A\x86\x36\x41\x48\xDA\xFD\xDF\x57\x68\x12\x41\x68\xDA\xFD\xDF\x67\x3B\x81\x4B\x88\xD7\xFD\xDF\x67\x3B\x61\x8C\xB8\xDA\xFD\xDF\x67\x13\x11\x44\xB8\xDD\xFD\xDF\x6A\x21\x14\x43\xEB\xDD\xFD\xDF\x7A\x25\x25\xB4\xDE\xDD\xFD\xDF\x7D\x5B\x63\xBB\xDD\xDD\xFD\xDF\xAD\xD7\x6A\x84\xDE\xDD\xFD\xDF\xDD\xD7\x2E\xE3\xEC\xDD\xFD\xDF\xDD\xEA\x5C\xCE\xCC\xDE\x9D\xFF\x9F\xCE\xEC\xCC\xCC\xEC\x9A", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x52\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x53\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x51\x81\x5E\x82\x50\x82\x50\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5A\x6B\x1F\x4B\xFE\x42\xF9\x5E\xB8\x4E\x36\x36\x31\x52\x9C\x73\xC4\x24\x8B\x45\xAE\x35\x86\x7D\x4D\x21\x06\x2D\xFF\x7F\xFF\xFF\xFF\x88\x88\xFF\xFF\xFF\xCF\xCC\xAC\x77\x77\xCA\xCC\xFC\xCF\xCC\x5A\x22\x33\xC5\xCC\xFC\xCF\xCC\x25\x32\x33\x73\xCC\xFC\xCF\xCC\x25\x33\x33\x73\xCC\xFC\xCF\xCC\x25\x33\x23\xB3\xCC\xFC\xCF\xCC\x67\xBB\xBB\xB6\xCC\xFC\xCF\xAC\xEB\xDE\xED\xDE\xC7\xFC\xCF\x7C\x65\x5B\x6B\xDB\xC7\xFC\xCF\x7C\x37\x22\x26\xB6\xCC\xFC\xCF\xCC\x67\x52\x66\xCD\xCC\xFC\xCF\xCC\x6A\x33\x63\xAE\xCC\xFC\xCF\xAC\x59\xDB\xED\xEB\xCA\xFC\xC8\x9A\x1E\xB4\xBB\xE7\xA9\x8C\xEA\x99\x7E\xE1\x4E\xE7\xE9\xAE\xEE\xE9\xAE\xB4\x7E\xEB\xE9\xEE", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x53\x81\x5E\x82\x51\x82\x58\x81\x46\x82\x53\x82\x53\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x52\x81\x5E\x82\x50\x82\x50\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5C\x67\xB9\x4A\x06\x2D\x12\x3A\xEE\x61\xD1\x49\xCA\x6D\xA8\x7D\x90\x31\x86\x7D\xD5\x1C\x08\x25\xD1\x1C\xEB\x1C\xFF\x7F\xFF\xFF\xFF\x11\x11\xFF\xFF\xFF\xAF\xAA\xDA\xDB\xBD\xA9\xAA\xFA\xAF\xBA\xBB\xBD\xBD\x9D\xAA\xFA\xAF\xDA\xBD\xBB\xDD\xDD\xA5\xFA\xAF\x9A\xDD\xBB\xED\xDD\x59\xFA\xAF\xBA\xDD\x9C\xEC\xC9\xDD\xFA\xAF\xBA\xEE\xCE\x9E\xEE\xDD\xFA\xAF\xBA\x9E\x12\x11\xE2\xB9\xFA\xAF\x9A\x44\x44\x22\xE4\xB5\xFA\x81\x66\x49\xC9\x24\x9C\xDA\xFA\xB6\xDB\x4C\xF1\x21\xE9\xDA\xFA\xDB\x36\x94\x12\x21\xE9\x9A\xFA\x71\x33\x41\x29\x91\xAE\xAA\xFA\x35\x93\x1F\x9E\xE9\x33\xAA\xFA\x33\x93\x1F\x44\x1E\x39\x83\xFA\x33\x93\x11\x24\x19\x39\x13\xFF", 256),
        QByteArray::fromRawData("\x53\x43\x11\x01\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x54\x81\x5E\x82\x58\x82\x58\x81\x46\x82\x54\x82\x58\x00\x00\x00\x00\x82\x65\x82\x65\x82\x56\x81\x5E\x82\x72\x82\x60\x82\x75\x82\x64\x82\x50\x82\x53\x81\x5E\x82\x50\x82\x50\x81\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5C\x67\x37\x67\xB9\x4E\xB2\x5A\x37\x3A\x34\x42\x50\x4E\xCF\x39\xA8\x71\xAA\x59\xAB\x45\xAC\x35\x86\x7D\x29\x25\xFF\x7F\x1F\x77\xEB\xEE\xF2\x21\x42\xEE\x9F\xB7\xBE\xE8\xFC\x2F\x22\xB4\x9F\xE7\xEE\x68\x46\x2F\x24\x42\x9F\xE4\x39\xF1\x63\x42\x24\x74\x9F\xE2\x19\xFF\x61\x44\x47\x44\x9F\xE1\x19\xFF\x83\x47\xCC\x77\xDF\xE2\xBD\x51\x8E\x78\x6C\x8C\xDF\xE4\xAD\x13\x63\x87\x68\xEC\xDF\xE4\x9D\xF1\xFF\xC7\x68\xEC\xDF\xB7\xDD\x14\xFF\xE7\x55\xCE\xDF\xBA\xDD\x6B\xF1\xE6\x65\xCE\xDF\xAD\x9A\x4E\xF1\xE3\xE5\xCC\xDF\x9D\xEE\xEE\x11\xE5\xE3\xCC\xDF\xDD\xE8\xEE\xEE\xE5\xE1\x8C\xDF\xDD\x8C\xEE\xEE\x45\xE1\x8C\xFF\xFF\xC1\xE8\xEE\x13\xE3\x78", 256)
    };
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PSV SAVE INFO~~~~~~~~~~~~~~~~~~~~~~~~~*/
    static const int PS3_FILE_SIZE = 0x2084;
    static const int PS3_FILE_HEADER_SIZE = 0x0084;
    inline static const QString PS3_FILE_DESCRIPTION = tr("PSV Save File");
    inline static const QStringList PS3_VALID_EXTENSIONS { QStringLiteral("*.PSV")};
    inline static const QRegExp PS3_VALID_NAME_REGEX = QRegExp(QStringLiteral("(BASCUS|BESCES|BISLPS)-\\d{5}4646372D533(13[0-5]|03[1-9]).PSV"));
    inline static const QByteArray PS3_FILE_ID = QByteArray::fromRawData("\x00\x56\x53\x50", 4);
    static const int PS3_SEED_OFFSET = 0x0008;
    static const int PS3_SIGNATURE_OFFSET = 0x001C;
    static const int PS3_FILE_TYPE_OFFSET = 0x0038;
    static const int PS3_FILE_DISP_SIZE_OFFSET = 0x0040;
    static const int PS3_FILE_SIZE_OFFSET = 0x005C;
    inline static const QByteArray PS3_FILE_HEADER = QByteArray::fromRawData("\x00\x56\x53\x50\x00\x00\x00\x00\x04\xbc\x97\x58\x11\x0f\x7e\x85\xc7\x4f\x2f\xd0\x5a\x28\xb6\x25\xe6\x9a\x6e\xa1\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x20\x00\x00\x84\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x03\x90\x00\x00\x42\x41\x53\x43\x55\x53\x2d\x39\x34\x31\x36\x33\x46\x46\x37\x2d\x53\x30\x31\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", PS3_FILE_HEADER_SIZE);
    /*~~~~~~~ PSV / PSP Common Signing ~~~~~~~~~~~~~~*/
    static const int PS_SIGNATURE_SIZE = 0x0014;
    inline static const QByteArray PS_SIGNING_KEY= QByteArray::fromRawData("\xAB\x5A\xBC\x9F\xC1\xF4\x9D\xE6\xA0\x51\xDB\xAE\xFA\x51\x88\x59", 0x10);
    inline static const QByteArray PS_SIGNING_IV= QByteArray::fromRawData("\xB3\x0F\xFE\xED\xB7\xDC\x5E\xB7\x13\x3D\xA6\x0D\x1B\x6B\x2C\xDC", 0x10);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PS4 SAVE INFO~~~~~~~~~~~~~~~~~~~~~~~~~*/
    static const int PS4_FILE_SIZE = 0xA00000;
    static const int PS4_FILE_HEADER_SIZE = 0x00AF;
    inline static const QString PS4_FILE_DESCRIPTION = tr("PS4 Save File");
    inline static const QStringList PS4_VALID_EXTENSIONS { QStringLiteral("*.ff7") };
    inline static const QRegExp PS4_VALID_NAME_REGEX = QRegExp(QStringLiteral("save0[0-9].ff7"));
    inline static const QByteArray PS4_FILE_ID = QByteArray::fromRawData("\x17\x00\x00\x00\x00\x00\x00\x00", 8);
    static const int PS4_BINFILE_SIZE = 0x60;
    static const int PS4_SEED_OFFSET = 0x0008;
    static const int PS4_SIGNATURE_OFFSET = 0x001C;
    static const int PS4_FILE_TYPE_OFFSET = 0x0038;
    static const int PS4_FILE_DISP_SIZE_OFFSET = 0x0040;
    static const int PS4_FILE_SIZE_OFFSET = 0x005C;
    inline static const QByteArray PS4_FILE_HEADER = QByteArray::fromRawData("\x00\x56\x53\x50\x00\x00\x00\x00\x04\xbc\x97\x58\x11\x0f\x7e\x85\xc7\x4f\x2f\xd0\x5a\x28\xb6\x25\xe6\x9a\x6e\xa1\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x14\x00\x00\x00\x01\x00\x00\x00\x00\x20\x00\x00\x84\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x20\x00\x00\x03\x90\x00\x00\x42\x41\x53\x43\x55\x53\x2d\x39\x34\x31\x36\x33\x46\x46\x37\x2d\x53\x30\x31\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", PS3_FILE_HEADER_SIZE);
    /*~~~~~~~ PS4 Signing ~~~~~~~~~~~~~~*/
    static const int PS4_SIGNATURE_SIZE = 0x0014;
    inline static const QByteArray PS4_SIGNING_KEY= QByteArray::fromRawData("\xAB\x5A\xBC\x9F\xC1\xF4\x9D\xE6\xA0\x51\xDB\xAE\xFA\x51\x88\x59", 0x10);
    inline static const QByteArray PS4_SIGNING_IV= QByteArray::fromRawData("\xB3\x0F\xFE\xED\xB7\xDC\x5E\xB7\x13\x3D\xA6\x0D\x1B\x6B\x2C\xDC", 0x10);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Mem Card Format~~~~~~~~~~~~~~~~~~~*/
    static const int VMC_FILE_SIZE = 0x20000;
    static const int VMC_FILE_HEADER_SIZE = 0x2000;
    inline static const QString VMC_FILE_DESCRIPTION = tr("Virtual Memory Card");
    inline static const QStringList VMC_VALID_EXTENSIONS {
        QStringLiteral("*.mcr"), QStringLiteral("*.mcd"), QStringLiteral("*.mci"),
        QStringLiteral("*.mc"), QStringLiteral("*.ddf"), QStringLiteral("*.ps"),
        QStringLiteral("*.psm"), QStringLiteral("*.VM1"), QStringLiteral("*.bin"), QStringLiteral("*.srm")};
    inline static const QRegExp VMC_VALID_NAME_REGEX = QRegExp(QStringLiteral("\\S+.(mc[r|d|i]?|ddf|ps[m]?]|bin|srm|VM1)"), Qt::CaseInsensitive);
    inline static const QByteArray VMC_FILE_ID = "\x4D\x43";
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PSP SAVE FORMAT~~~~~~~~~~~~~~~~~~~*/
    static const int PSP_FILE_SIZE = 0x20080;
    static const int PSP_FILE_HEADER_SIZE = 0x2080;
    inline static const QString PSP_FILE_DESCRIPTION = tr("PSP and PsVita Virtual Memory Card");
    inline static const QStringList PSP_VALID_EXTENSIONS { QStringLiteral("*.VMP")};
    inline static const QRegExp PSP_VALID_NAME_REGEX = QRegExp(QStringLiteral("\\S+.VMP"));
    inline static const QByteArray PSP_FILE_ID = QByteArray::fromRawData("\x00\x50\x4D\x56\x80", 5);
    static const int PSP_SEED_OFFSET = 0x000C;
    static const int PSP_SIGNATURE_OFFSET = 0x0020;
    inline static const QByteArray PSP_FILE_HEADER = QByteArray::fromRawData("\x00\x50\x4D\x56\x80\x00\x00\x00\x00\x00\x00\x00\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x54\x37\x42\x51\xEE\xB0\x88\xDB\x2E\xBD\xA5\x09\x24\xB6\x5C\x17\x6D\xED\x87\x36\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 128);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~VGS SAVE FORMAT~~~~~~~~~~~~~~~~~~~~*/
    static const int VGS_FILE_SIZE = 0x20040;
    static const int VGS_FILE_HEADER_SIZE = 0x2040;
    inline static const QString VGS_FILE_DESCRIPTION = tr("Virtual Game Station Memory Card");
    inline static const QStringList VGS_VALID_EXTENSIONS { QStringLiteral("*.vgs"), QStringLiteral("*.mem")};
    inline static const QRegExp VGS_VALID_NAME_REGEX = QRegExp(QStringLiteral("\\S+.(vgs|mem)"), Qt::CaseInsensitive);
    inline static const QByteArray VGS_FILE_ID = "\x56\x67\x73\x4D";
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~DEX SAVE FORMAT~~~~~~~~~~~~~~~~~~~~*/
    static const int DEX_FILE_SIZE = 0x20F40;
    static const int DEX_FILE_HEADER_SIZE = 0x2F40;
    inline static const QString DEX_FILE_DESCRIPTION = tr("DEX Drive Virtual Memory Card");
    inline static const QStringList DEX_VALID_EXTENSIONS {QStringLiteral("*.gme")};
    inline static const QRegExp DEX_VALID_NAME_REGEX = QRegExp(QStringLiteral("\\S+.gme"), Qt::CaseInsensitive);
    inline static const QByteArray DEX_FILE_ID = QByteArray::fromRawData("\x31\x32\x33\x2D\x34\x35\x36\x2D\x53\x54\x44\x00\x00\x00\x00\x00\x00\x00\x01\x00\x01\x4D", 22);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PGE SAVE FORMAT~~~~~~~~~~~~~~~~~~~*/
    static const int PGE_FILE_SIZE = 0x2080;
    static const int PGE_FILE_HEADER_SIZE = 0x0080;
    inline static const QString PGE_FILE_DESCRIPTION = tr("PSXGameEdit Memory Juggler");
    inline static const QStringList PGE_VALID_EXTENSIONS { QStringLiteral("*.mcs"), QStringLiteral("*.ps1")};
    inline static const QRegExp PGE_VALID_NAME_REGEX = QRegExp(QStringLiteral("\\S+.(mcs|ps1)"), Qt::CaseInsensitive);
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PDA SAVE FORMAT~~~~~~~~~~~~~~~~~~~*/
    static const int PDA_FILE_SIZE = 0x2036;
    static const int PDA_FILE_HEADER_SIZE = 0x0036;
    inline static const QString PDA_FILE_DESCRIPTION = tr("XP AR GS Caetla SmartLink Dantel");
    inline static const QStringList PDA_VALID_EXTENSIONS { QStringLiteral("*.mcb"), QStringLiteral("*.mcx"),QStringLiteral("*.psx"), QStringLiteral("*.pda")};
    inline static const QRegExp PDA_VALID_NAME_REGEX = QRegExp(QStringLiteral("\\S+.(psx|mcb|mcx|pda)"), Qt::CaseInsensitive);
};

FF7SaveInfo *FF7SaveInfo::instance()
{
    static FF7SaveInfo m;
    return &m;
}

FF7SaveInfo::FF7SaveInfo(QObject *parent) :
    QObject(parent)
    , d(new FF7SaveInfoPrivate)
{
}

FF7SaveInfo::~FF7SaveInfo()
{
    delete d;
}

QObject *FF7SaveInfo::qmlSingletonRegister(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    engine->setObjectOwnership(instance(), QQmlEngine::CppOwnership);
    return instance();
}

int FF7SaveInfo::fileSize(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSX): return d->PSX_FILE_SIZE;
    case (FORMAT::PC): return d->PC_FILE_SIZE;
    case (FORMAT::VMC): return d->VMC_FILE_SIZE;
    case (FORMAT::PSP): return d->PSP_FILE_SIZE;
    case (FORMAT::PS3): return d->PS3_FILE_SIZE;
    case (FORMAT::PS4): return d->PS4_FILE_SIZE;
    case (FORMAT::PS4BIN): return d->PS4_BINFILE_SIZE;
    case (FORMAT::DEX): return d->DEX_FILE_SIZE;
    case (FORMAT::VGS): return d->VGS_FILE_SIZE;
    case (FORMAT::SWITCH): return d->SWITCH_FILE_SIZE;
    case FORMAT::PGE: return d->PGE_FILE_SIZE;
    case FORMAT::PDA: return d->PDA_FILE_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::fileHeaderSize(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PC): return d->PC_FILE_HEADER_SIZE;
    case (FORMAT::VMC): return d->VMC_FILE_HEADER_SIZE;
    case (FORMAT::PSP): return d->PSP_FILE_HEADER_SIZE;
    case (FORMAT::PS3): return d->PS3_FILE_HEADER_SIZE;
    case (FORMAT::PS4): return d->PS4_FILE_HEADER_SIZE;
    case (FORMAT::DEX): return d->DEX_FILE_HEADER_SIZE;
    case (FORMAT::VGS): return d->VGS_FILE_HEADER_SIZE;
    case (FORMAT::SWITCH): return d->SWITCH_FILE_HEADER_SIZE;
    case FORMAT::PGE: return d->PGE_FILE_HEADER_SIZE;
    case FORMAT::PDA: return d->PDA_FILE_HEADER_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotHeaderSize(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSX):
    case (FORMAT::VMC):
    case (FORMAT::PSP):
    case (FORMAT::PS3):
    case (FORMAT::PS4):
    case (FORMAT::DEX):
    case FORMAT::PGE:
    case FORMAT::PDA:
    case (FORMAT::VGS): return d->PSX_SLOT_HEADER_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotFooterSize(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSX):
    case (FORMAT::VMC):
    case (FORMAT::PSP):
    case (FORMAT::PS3):
    case (FORMAT::PS4):
    case (FORMAT::DEX):
    case FORMAT::PGE:
    case FORMAT::PDA:
    case (FORMAT::VGS): return d->PSX_SLOT_FOOTER_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotCount(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case FORMAT::PDA:
    case FORMAT::PGE:
    case (FORMAT::PSX):
    case (FORMAT::PS3): return 1;
    case (FORMAT::PS4): return 1;
    case (FORMAT::VMC):
    case (FORMAT::PSP):
    case (FORMAT::DEX):
    case (FORMAT::VGS):
    case (FORMAT::SWITCH):
    case (FORMAT::PC): return 15;
    default: return 0;
    }
}

QByteArray FF7SaveInfo::fileIdentifier(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSX): return d->PSX_FILE_ID;
    case (FORMAT::PC): return d->PC_FILE_ID;
    case (FORMAT::VMC): return d->VMC_FILE_ID;
    case (FORMAT::PSP): return d->PSP_FILE_ID;
    case (FORMAT::PS3): return d->PS3_FILE_ID;
    case (FORMAT::PS4): return d->PS4_FILE_ID;
    case (FORMAT::DEX): return d->DEX_FILE_ID;
    case (FORMAT::VGS): return d->VGS_FILE_ID;
    case (FORMAT::SWITCH): return d->SWITCH_FILE_ID;
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::fileHeader(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PC):
    case (FORMAT::SWITCH):
    case (FORMAT::DEX):
    case (FORMAT::VGS):
    case (FORMAT::VMC): return QByteArray(fileIdentifier(format)).append(fileHeaderSize(format) - fileIdentifier(format).length(), 0x00);
    case (FORMAT::PSP): return d->PSP_FILE_HEADER;
    case (FORMAT::PS3): return d->PS3_FILE_HEADER;
    case (FORMAT::PS4): return d->PS4_FILE_HEADER;
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::slotHeader(FF7SaveInfo::FORMAT format, int slot) const
{
    std::clamp(slot, 0, 14);
    switch (format) {
    case FORMAT::PDA:
    case FORMAT::PGE:
    case (FORMAT::PSX):
    case (FORMAT::PSP):
    case (FORMAT::PS3):
    case (FORMAT::PS4):
    case (FORMAT::DEX):
    case (FORMAT::VGS):
    case (FORMAT::VMC): return QByteArray(d->PSX_SLOT_HEADER.at(slot)).append(256, 0x00);
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::slotFooter(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case FORMAT::PGE:
    case FORMAT::PDA:
    case (FORMAT::PSX):
    case (FORMAT::PSP):
    case (FORMAT::PS3):
    case (FORMAT::PS4):
    case (FORMAT::DEX):
    case (FORMAT::VGS):
    case (FORMAT::VMC): return QByteArray(d->PSX_SLOT_FOOTER_SIZE, 0x00);
    default: return QByteArray();
    }
}

QByteArray FF7SaveInfo::signingKey(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSP):
    case (FORMAT::PS3): return d->PS_SIGNING_KEY;
    default: return QByteArray();
    }
}

int FF7SaveInfo::extraPSVOffsets(FF7SaveInfo::PSVINFO info) const
{
    switch (info) {
    case PSVINFO::SAVETYPE: return d->PS3_FILE_TYPE_OFFSET;
    case PSVINFO::SIZEDISPLAY: return d->PS3_FILE_DISP_SIZE_OFFSET;
    case PSVINFO::SAVESIZE: return d->PS3_FILE_SIZE_OFFSET;
    default: return -1;
    }
}


QByteArray FF7SaveInfo::signingIV(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSP):
    case (FORMAT::PS3): return d->PS_SIGNING_IV;
    default: return QByteArray();
    }
}

int FF7SaveInfo::fileSeedOffset(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSP): return d->PSP_SEED_OFFSET;
    case (FORMAT::PS3): return d->PS3_SEED_OFFSET;
    default: return -1;
    }
}

int FF7SaveInfo::fileSignatureOffset(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSP): return d->PSP_SIGNATURE_OFFSET;
    case (FORMAT::PS3): return d->PS3_SIGNATURE_OFFSET;
    default: return -1;
    }
}

int FF7SaveInfo::fileSignatureSize(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PSP):
    case (FORMAT::PS3): return d->PS_SIGNATURE_SIZE;
    default: return 0;
    }
}

int FF7SaveInfo::slotSize() const
{
    return d->_slotSize;
}

QRegExp FF7SaveInfo::validNameRegExp(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PC): return d->PC_VALID_NAME_REGEX;
    case (FORMAT::PSX): return d->PSX_VALID_NAME_REGEX;
    case (FORMAT::PSP): return d->PSP_VALID_NAME_REGEX;
    case (FORMAT::PS3): return d->PS3_VALID_NAME_REGEX;
    case (FORMAT::PS4): return d->PS4_VALID_NAME_REGEX;
    case (FORMAT::DEX): return d->DEX_VALID_NAME_REGEX;
    case (FORMAT::VGS): return d->VGS_VALID_NAME_REGEX;
    case (FORMAT::VMC): return d->VMC_VALID_NAME_REGEX;
    case (FORMAT::SWITCH): return d->SWITCH_VALID_NAME_REGEX;
    case FORMAT::PGE: return d->PGE_VALID_NAME_REGEX;
    case FORMAT::PDA: return d->PDA_VALID_NAME_REGEX;
    default: return QRegExp(QStringLiteral(""));
    }
}

QString FF7SaveInfo::typeDescription(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PC): return d->PC_FILE_DESCRIPTION;
    case (FORMAT::PSX): return d->PSX_FILE_DESCRIPTION;
    case (FORMAT::PSP): return d->PSP_FILE_DESCRIPTION;
    case (FORMAT::PS3): return d->PS3_FILE_DESCRIPTION;
    case (FORMAT::PS4): return d->PS4_FILE_DESCRIPTION;
    case (FORMAT::DEX): return d->DEX_FILE_DESCRIPTION;
    case (FORMAT::VGS): return d->VGS_FILE_DESCRIPTION;
    case (FORMAT::VMC): return d->VMC_FILE_DESCRIPTION;
    case (FORMAT::SWITCH): return d->SWITCH_FILE_DESCRIPTION;
    case FORMAT::PGE: return d->PGE_FILE_DESCRIPTION;
    case FORMAT::PDA: return d->PDA_FILE_DESCRIPTION;
    default: return QString();
    }
}

QStringList FF7SaveInfo::typeExtension(FF7SaveInfo::FORMAT format) const
{
    switch (format) {
    case (FORMAT::PC): return d->PC_VALID_EXTENSIONS;
    case (FORMAT::PSX): return d->PSX_VALID_EXTENSIONS;
    case (FORMAT::PSP): return d->PSP_VALID_EXTENSIONS;
    case (FORMAT::PS3): return d->PS3_VALID_EXTENSIONS;
    case (FORMAT::PS4): return d->PS4_VALID_EXTENSIONS;
    case (FORMAT::DEX): return d->DEX_VALID_EXTENSIONS;
    case (FORMAT::VGS): return d->VGS_VALID_EXTENSIONS;
    case (FORMAT::VMC): return d->VMC_VALID_EXTENSIONS;
    case (FORMAT::SWITCH): return d->SWITCH_VALID_EXTENSIONS;
    case FORMAT::PGE: return d->PGE_VALID_EXTENSIONS;
    case FORMAT::PDA: return d->PDA_VALID_EXTENSIONS;
    default: return QStringList();
    }
}

QString FF7SaveInfo::typeFilter(FF7SaveInfo::FORMAT format) const
{
    if (format == FORMAT::UNKNOWN)
        return tr("All Files (*)");
    return QStringLiteral("%1 (%2)").arg(typeDescription(format), typeExtension(format).join(QStringLiteral(" ")));
}

QString FF7SaveInfo::knownTypesFilter() const
{
    QString allTypes = QStringLiteral("%1 %2 %3 %4 %5 %6 %7 %8 %9 %10 %11")
        .arg(d->PC_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->PSX_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->PSP_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->PS3_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->PS4_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->DEX_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->VGS_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->VMC_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->SWITCH_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->PGE_VALID_EXTENSIONS.join(QStringLiteral(" ")))
        .arg(d->PDA_VALID_EXTENSIONS.join(QStringLiteral(" ")));

    return QStringLiteral("%1;;%2;;%3;;%4;;%5;;%6;;%7;;%8;;%9;;%10;;%11;;%12;;%13")
        .arg(tr("Known FF7 Save Types (%1)").arg(allTypes))
        .arg(typeFilter(FORMAT::PC))
        .arg(typeFilter(FORMAT::SWITCH))
        .arg(typeFilter(FORMAT::VMC))
        .arg(typeFilter(FORMAT::PSX))
        .arg(typeFilter(FORMAT::PS3))
        .arg(typeFilter(FORMAT::PS4))
        .arg(typeFilter(FORMAT::PSP))
        .arg(typeFilter(FORMAT::DEX))
        .arg(typeFilter(FORMAT::VGS))
        .arg(typeFilter(FORMAT::PGE))
        .arg(typeFilter(FORMAT::PDA))
        .arg(typeFilter(FORMAT::UNKNOWN));
}
