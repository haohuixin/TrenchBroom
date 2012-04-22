/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_NUMERICUPDOWN_H
#define GWEN_CONTROLS_NUMERICUPDOWN_H

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/TextBox.h"

namespace Gwen 
{
	namespace Controls
	{
		class NumericUpDownButton_Up : public Button
		{
			GWEN_CONTROL_INLINE( NumericUpDownButton_Up, Button )
			{
				SetSize( 7, 7 );
			}

			virtual void Render( Skin::Base* skin )
			{
				skin->DrawNumericUpDownButton( this, IsDepressed(), true );
			}
		};

		class NumericUpDownButton_Down : public Button
		{
			GWEN_CONTROL_INLINE( NumericUpDownButton_Down, Button )
			{
				SetSize( 7, 7 );
			}

			virtual void Render( Skin::Base* skin )
			{
				skin->DrawNumericUpDownButton( this, IsDepressed(), false );
			}
		};

		class NumericUpDown : public TextBoxNumeric
		{
			public:

				GWEN_CONTROL( NumericUpDown, TextBoxNumeric );

				virtual void SetMin( int i );
				virtual void SetMax( int i );
				virtual void SetValue( int i );

				Event::Caller	onChanged;

			private:

				virtual void OnEnter();
				virtual void OnChange();
				virtual void OnTextChanged();

				virtual void OnButtonUp( Base* control );
				virtual void OnButtonDown( Base* control );

				virtual bool OnKeyUp( bool bDown )	{	if ( bDown ) OnButtonUp( NULL ); return true;   }
				virtual bool OnKeyDown( bool bDown ){	if ( bDown ) OnButtonDown( NULL ); return true; }

				virtual void SyncTextFromNumber();
				virtual void SyncNumberFromText();

				

				int m_iNumber;
				int m_iMax;
				int m_iMin;

		};
	}
}
#endif