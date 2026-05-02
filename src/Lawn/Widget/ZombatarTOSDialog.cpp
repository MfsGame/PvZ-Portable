/*
 * Copyright (C) 2026 Zhou Qiankang <wszqkzqk@qq.com>
 *
 * SPDX-License-Identifier: LGPL-3.0-or-later
 *
 * This file is part of PvZ-Portable.
 *
 * PvZ-Portable is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PvZ-Portable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with PvZ-Portable. If not, see <https://www.gnu.org/licenses/>.
 */

#include "ZombatarTOSDialog.h"
#include "../../LawnApp.h"
#include "../../Resources.h"
#include "../../GameConstants.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/graphics/Graphics.h"
#include "../../SexyAppFramework/graphics/Font.h"
#include "../../SexyAppFramework/graphics/Image.h"
#include "../../SexyAppFramework/widget/WidgetManager.h"

static constexpr int TOS_DIALOG_W = 640;
static constexpr int TOS_MAX_TEXT_H = 370;
static constexpr int TOS_TEXT_MARGIN = 28;

ZombatarTOSDialog::ZombatarTOSDialog(LawnApp* theApp) :
	LawnDialog(theApp,
		Dialogs::DIALOG_ZOMBATAR_TOS,
		true,
		"[ZOMBATAR_TOS_HEADER]",
		"[ZOMBATAR_TOS]",
		"",
		Dialog::BUTTONS_OK_CANCEL)
{
	mSlider = nullptr;
	mScrollOffset = 0;
	mTextAreaHeight = 0;
	mTotalTextHeight = 0;
	mDrawStandardBack = true;

	Graphics g;
	g.SetFont(mLinesFont);
	int aTextWidth = TOS_DIALOG_W - TOS_TEXT_MARGIN * 2 - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - 4;
	mTotalTextHeight = GetWordWrappedHeight(&g, aTextWidth, mDialogLines, mLinesFont->GetLineSpacing() + mLineSpacingOffset);

	int aDialogWidth = TOS_DIALOG_W;
	int aTopMidWidth = Sexy::IMAGE_DIALOG_TOPMIDDLE->mWidth;
	int aImageWidth = Sexy::IMAGE_DIALOG_TOPLEFT->mWidth + Sexy::IMAGE_DIALOG_TOPRIGHT->mWidth + aTopMidWidth;
	if (aDialogWidth < aImageWidth)
		aDialogWidth = aImageWidth;
	else if (aTopMidWidth > 0)
	{
		int anExtraWidth = (aDialogWidth - aImageWidth) % aTopMidWidth;
		if (anExtraWidth) aDialogWidth += aTopMidWidth - anExtraWidth;
	}

	int aTextStartY = mContentInsets.mTop + mBackgroundInsets.mTop + DIALOG_HEADER_OFFSET;
	if (mDialogHeader.size() > 0)
		aTextStartY += mHeaderFont->GetHeight() + mSpaceAfterHeader;

	mTextAreaHeight = std::min(mTotalTextHeight, TOS_MAX_TEXT_H);

	int aDialogHeight = aTextStartY + mTextAreaHeight + mContentInsets.mBottom + mBackgroundInsets.mBottom + mButtonHeight + 55;
	if (mTallBottom) aDialogHeight += 36;

	int aBottomHeight = (mTallBottom ? Sexy::IMAGE_DIALOG_BIGBOTTOMLEFT : Sexy::IMAGE_DIALOG_BOTTOMLEFT)->mHeight;
	int aImageHeight = Sexy::IMAGE_DIALOG_TOPLEFT->mHeight + aBottomHeight + DIALOG_HEADER_OFFSET;
	if (aDialogHeight < aImageHeight) aDialogHeight = aImageHeight;
	else
	{
		int aCenterHeight = Sexy::IMAGE_DIALOG_CENTERLEFT->mHeight;
		int anExtraHeight = (aDialogHeight - aImageHeight) % aCenterHeight;
		if (anExtraHeight) aDialogHeight += aCenterHeight - anExtraHeight;
	}

	Resize((BOARD_WIDTH - aDialogWidth) / 2, (BOARD_HEIGHT - aDialogHeight) / 2, aDialogWidth, aDialogHeight);
}

ZombatarTOSDialog::~ZombatarTOSDialog()
{
	delete mSlider;
}

void ZombatarTOSDialog::AddedToManager(WidgetManager* theWidgetManager)
{
	LawnDialog::AddedToManager(theWidgetManager);

	int aTextAreaLeft = mBackgroundInsets.mLeft + mContentInsets.mLeft + TOS_TEXT_MARGIN;
	int aTextAreaWidth = mWidth - TOS_TEXT_MARGIN * 2 - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - 4;

	int aTextStartY = mContentInsets.mTop + mBackgroundInsets.mTop + DIALOG_HEADER_OFFSET;
	if (mDialogHeader.size() > 0)
		aTextStartY += mHeaderFont->GetHeight() + mSpaceAfterHeader;

	if (mTotalTextHeight > mTextAreaHeight)
	{
		mSlider = new Slider(IMAGE_ZOMBATAR_TOS_SLIDER, IMAGE_ZOMBATAR_TOS_SLIDER_THUMB, 0, this);
		mSlider->Resize(
			aTextAreaLeft + aTextAreaWidth + 8,
			aTextStartY,
			24,
			mTextAreaHeight);
		theWidgetManager->AddWidget(mSlider);
	}
}

void ZombatarTOSDialog::RemovedFromManager(WidgetManager* theWidgetManager)
{
	if (mSlider)
	{
		theWidgetManager->RemoveWidget(mSlider);
		delete mSlider;
		mSlider = nullptr;
	}

	LawnDialog::RemovedFromManager(theWidgetManager);
}

void ZombatarTOSDialog::MouseWheel(int theDelta)
{
	mScrollOffset -= theDelta * 20;
	if (mScrollOffset < 0) mScrollOffset = 0;
	int aMaxScroll = std::max(0, mTotalTextHeight - mTextAreaHeight);
	if (mScrollOffset > aMaxScroll) mScrollOffset = aMaxScroll;

	if (mSlider && aMaxScroll > 0)
		mSlider->SetValue(static_cast<double>(mScrollOffset) / aMaxScroll);

	MarkDirty();
}

void ZombatarTOSDialog::SliderVal(int theId, double theVal)
{
	(void)theId;
	int aMaxScroll = std::max(0, mTotalTextHeight - mTextAreaHeight);
	mScrollOffset = static_cast<int>(theVal * aMaxScroll);
	if (mScrollOffset < 0) mScrollOffset = 0;
	if (mScrollOffset > aMaxScroll) mScrollOffset = aMaxScroll;
	MarkDirty();
}

void ZombatarTOSDialog::Draw(Graphics* g)
{
	std::string aSavedLines = mDialogLines;
	mDialogLines = "";
	int aSavedBtnHeight = mButtonHeight;
	mButtonHeight = 0;

	LawnDialog::Draw(g);

	mDialogLines = aSavedLines;
	mButtonHeight = aSavedBtnHeight;

	int aTextAreaLeft = mBackgroundInsets.mLeft + mContentInsets.mLeft + TOS_TEXT_MARGIN;
	int aTextAreaWidth = mWidth - TOS_TEXT_MARGIN * 2 - mContentInsets.mLeft - mContentInsets.mRight - mBackgroundInsets.mLeft - mBackgroundInsets.mRight - 4;

	int aTextStartY = mContentInsets.mTop + mBackgroundInsets.mTop + DIALOG_HEADER_OFFSET;
	if (mDialogHeader.size() > 0)
		aTextStartY += mHeaderFont->GetHeight() + mSpaceAfterHeader;

	g->SetFont(mLinesFont);
	g->SetColor(mColors[Dialog::COLOR_LINES]);

	Rect aOldClip = g->mClipRect;
	g->SetClipRect(aTextAreaLeft - 2, aTextStartY - 2, aTextAreaWidth + 4, mTextAreaHeight + 4);

	Rect aRect(aTextAreaLeft + 2, aTextStartY + 2 - mScrollOffset, aTextAreaWidth, 0);
	WriteWordWrapped(g, aRect, mDialogLines, mLinesFont->GetLineSpacing() + mLineSpacingOffset, mTextAlign);

	g->SetClipRect(aOldClip);
}
