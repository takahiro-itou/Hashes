﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---   Hash Functions Library   ---                  **
**                                                                      **
**          Copyright (C), 2025-2025, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      プロジェクトの設定。
**
**      @file       Common/HashesSettings.h
**/

#if !defined( HASHES_COMMON_INCLUDED_HASHES_SETTINGS_H )
#    define   HASHES_COMMON_INCLUDED_HASHES_SETTINGS_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if defined( HASHES_USE_PRE_CONFIGURED_MSVC )
#    include    "Hashes/.Config/PreConfigHashes.msvc.h"
#else
#    include    "Hashes/.Config/ConfiguredHashes.h"
#endif

HASHES_NAMESPACE_BEGIN

HASHES_NAMESPACE_END

#endif
