//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2011, John Haddon. All rights reserved.
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

#include "Gaffer/Node.h"
#include "Gaffer/ScriptNode.h"

using namespace Gaffer;

IE_CORE_DEFINERUNTIMETYPED( Node );

Node::Node( const std::string &name )
	:	GraphComponent( name )
{
}

Node::~Node()
{
}

PlugIterator Node::plugsBegin() const
{
	return PlugIterator( children().begin(), children().end() );
}

PlugIterator Node::plugsEnd() const
{
	return PlugIterator( children().end(), children().end() );
}

InputPlugIterator Node::inputPlugsBegin() const
{
	return InputPlugIterator( children().begin(), children().end() );
}

InputPlugIterator Node::inputPlugsEnd() const
{
	return InputPlugIterator( children().end(), children().end() );
}

OutputPlugIterator Node::outputPlugsBegin() const
{
	return OutputPlugIterator( children().begin(), children().end() );
}

OutputPlugIterator Node::outputPlugsEnd() const
{
	return OutputPlugIterator( children().end(), children().end() );
}
		
Node::UnaryPlugSignal &Node::plugSetSignal()
{
	return m_plugSetSignal;
}

Node::UnaryPlugSignal &Node::plugDirtiedSignal()
{
	return m_plugDirtiedSignal;
}

Node::UnaryPlugSignal &Node::plugInputChangedSignal()
{
	return m_plugInputChangedSignal;
}

ScriptNodePtr Node::scriptNode()
{
	return ancestor<ScriptNode>();
}

ConstScriptNodePtr Node::scriptNode() const
{
	return ancestor<ScriptNode>();
}
		
bool Node::acceptsChild( ConstGraphComponentPtr potentialChild ) const
{
	if( !GraphComponent::acceptsChild( potentialChild ) )
	{
		return false;
	}
	return potentialChild->isInstanceOf( (IECore::TypeId)PlugTypeId ) || potentialChild->isInstanceOf( (IECore::TypeId)NodeTypeId );
}

bool Node::acceptsParent( const GraphComponent *potentialParent ) const
{
	if( !GraphComponent::acceptsParent( potentialParent ) )
	{
		return false;
	}
	return potentialParent->isInstanceOf( (IECore::TypeId)NodeTypeId );
}

void Node::dirty( ConstPlugPtr dirty ) const
{
}

void Node::compute( PlugPtr output ) const
{
}

void Node::parentChanging( Gaffer::GraphComponent *newParent )
{
	// if we're losing our parent then remove all connections first.
	// this must be done here rather than from parentChangedSignal()
	// because we need a current parent for the operation to be
	// undoable.
	
	if( !newParent )
	{
		for( InputPlugIterator it=inputPlugsBegin(); it!=inputPlugsEnd(); it++ )
		{
			(*it)->setInput( 0 );
		}

		for( OutputPlugIterator it=outputPlugsBegin(); it!=outputPlugsEnd(); it++ )
		{
			(*it)->removeOutputs();
		}
	}
}
