//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2014, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#ifndef GAFFERSCENE_DELETEGLOBALS_H
#define GAFFERSCENE_DELETEGLOBALS_H

#include "GafferScene/GlobalsProcessor.h"

namespace Gaffer
{

IE_CORE_FORWARDDECLARE( StringPlug )

} // namespace Gaffer

namespace GafferSceneModule
{

void bindGlobals(); // to enable friend declaration for bindDeleteGlobals().

} // namespace GafferSceneModule

namespace GafferScene
{

class DeleteGlobals : public GlobalsProcessor
{

	public :

		DeleteGlobals( const std::string &name=defaultName<DeleteGlobals>() );
		virtual ~DeleteGlobals();

		IE_CORE_DECLARERUNTIMETYPEDEXTENSION( GafferScene::DeleteGlobals, DeleteGlobalsTypeId, GlobalsProcessor );

		Gaffer::StringPlug *namesPlug();
		const Gaffer::StringPlug *namesPlug() const;

		Gaffer::BoolPlug *invertNamesPlug();
		const Gaffer::BoolPlug *invertNamesPlug() const;

		virtual void affects( const Gaffer::Plug *input, AffectedPlugsContainer &outputs ) const;

	protected :

		virtual std::string namePrefix() const;

		virtual void hashProcessedGlobals( const Gaffer::Context *context, IECore::MurmurHash &h ) const;
		virtual IECore::ConstCompoundObjectPtr computeProcessedGlobals( const Gaffer::Context *context, IECore::ConstCompoundObjectPtr inputGlobals ) const;

	private :

		static size_t g_firstPlugIndex;

		friend void GafferSceneModule::bindGlobals();

};

IE_CORE_DECLAREPTR( DeleteGlobals );

} // namespace GafferScene

#endif // GAFFERSCENE_DELETEGLOBALS_H
