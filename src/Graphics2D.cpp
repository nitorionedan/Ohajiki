//------------------------------------------------------------------------------
/// @file
/// @brief		Graphics2D.hppの実装
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
///	@referenced	http://hpcgi2.nifty.com/natupaji/bbs/patio.cgi?mode=view&no=2295

//------------------------------------------------------------------------------

#include "DxLib.h"

#include "Graphics2D.hpp"
#include "Game.hpp"

#include <cmath>
#include <algorithm>

#undef max
#undef min

#define CIRCLE_ANGLE_VERTEX_NUM		16	// 円周の頂点数
#define CIRCLE_RADIUS_VERTEX_NUM	8	// 半径の頂点数


Graphics2D::Graphics2D()
	: FRAME_NUM(0)
	, gh(nullptr)
{
}


Graphics2D::Graphics2D(int Gr_Handle[], int num)
	: FRAME_NUM(num)
	, count(0)
{
	gh = new int[FRAME_NUM];

	for (int i = 0; i < FRAME_NUM; i++)
		gh[i] = Gr_Handle[i];
}


Graphics2D::~Graphics2D()
{
	delete[] gh;
}


void Graphics2D::Raster_Scroll(const int &X, const int &Y, const int &Gr_Handle, double Cycle,  double Shake)
{
	int Width = 0, Height = 0;	// 画像の横幅と縦幅
	int Correction = 0;			// ラスタースクロールの補正

	GetGraphSize(Gr_Handle, &Width, &Height);

	for (int I = 0; I < Height; ++I)
	{
		const int DestX = X - Width / 2 + std::cos((I + Correction) / 180.0 * DX_PI * Cycle) * Shake;
		const int DestY = Y - Height / 2 + I;

		DrawRectGraph
		(
			DestX, DestY,
			0, I,
			Width, 1,
			Gr_Handle,
			TRUE, FALSE
		);
	}

	++Correction;
}


void Graphics2D::DrawRasterScroll(const int& X, const int& Y, double Cycle, double Shake, const int& Gr_Handle, bool isVertical)
{
	int Width = 0, Height = 0;					// 画像の横幅と縦幅
	static int Correction = 0;					// ラスタースクロールの補正

	GetGraphSize(Gr_Handle, &Width, &Height);	// 画像のサイズを得る

	switch (isVertical)
	{
	case true :
		for (int I = 0; I < Height; ++I)
		{
			const int& DestX = X - Width / 2 + std::cos((I + Correction) / 180.0 * DX_PI * Cycle) * Shake;	// cosの値で左右に揺らす
			const int& DestY = Y - Height / 2 + I;

			// 画像の分割描画（縦に１pixずつ）
			DrawRectGraph(
				DestX, DestY,
				0, I,
				Width, 1,
				Gr_Handle,
				TRUE, FALSE
				);
		}
		break;

	case false :
		for (int I = 0; I < Width; ++I)
		{
			const int& DestX = X - Width / 2 + I;
			const int& DestY = Y - Height / 2 + std::cos((I + Correction) / 180. * DX_PI * Cycle) * Shake;

			// 画像の分割描画（横に１pixずつ）
			DrawRectGraph
				(
					DestX, DestY,
					I, 0,
					1, Height,
					Gr_Handle,
					TRUE, FALSE
				);
		}
		break;
	}

	++Correction;
}


void Graphics2D::DrawBlendAdd(const int &X, const int &Y, const double &ExRate_, const double &Angle_, int Blend_ADD, const int &Gr_Handle, bool TransFlag_)
{
	const int& BLEND_ADD = std::min( 255, std::max(0, Blend_ADD) );

	SetDrawBlendMode(DX_BLENDMODE_ADD, BLEND_ADD);					// 加算ブレンドモード
	DrawRotaGraph(X, Y, ExRate_, Angle_, Gr_Handle, TransFlag_);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);						//ブレンドモードをオフ
}


void Graphics2D::DrawColorGraph(const int& X, const int& Y, const double& Exrate, const int& Gr_Handle, int R, int G, int B)
{
	SetDrawBright(R, G, B);
	DrawRotaGraph(X, Y, Exrate, 0.0, Gr_Handle, true);
	SetDrawBright(255, 255, 255);
}


void DrawAnime(const double & PosX, const double & PosY, const double& ExRate, const double & ANGLE, const int & TIME, const int& FRAME_NUM, const int & TIME_FRAME, int Gr_Handle[], const bool& TurnFlag)
{
	// 余りをもとめるため、１を足して調整
	const int& SUM_FRAME_TIME = (FRAME_NUM * TIME_FRAME + 1);

	// アニメーション
	for (int j = 0; j < FRAME_NUM; j++)
	{
		const bool& IS_PLAYTIME = ( TIME % SUM_FRAME_TIME < j * TIME_FRAME ||
									TIME % SUM_FRAME_TIME > TIME_FRAME + (j * TIME_FRAME) );
		if (IS_PLAYTIME)	continue;

		DrawRotaGraph(PosX, PosY, ExRate, ANGLE, Gr_Handle[j], true, TurnFlag);
		break;
	}
}


void DrawAnime(const double & PosX, const double & PosY, const double& ExRate, const double & ANGLE,                   const int & FRAME_NUM, const int & TIME_FRAME, int Gr_Handle[], const bool& TurnFlag)
{
	// 余りをもとめるため、１を足して調整
	const int& SUM_FRAME_TIME = (FRAME_NUM * TIME_FRAME + 1);
	
	static int aniTime = 0;
	aniTime++;

	// アニメーション
	for (int j = 0; j < FRAME_NUM; j++)
	{
		const bool& IS_PLAYTIME = ( aniTime % SUM_FRAME_TIME < j * TIME_FRAME ||
									aniTime % SUM_FRAME_TIME > TIME_FRAME + (j * TIME_FRAME) );
		if (IS_PLAYTIME)	continue;

		DrawRotaGraph(PosX, PosY, ExRate, ANGLE, Gr_Handle[j], true, TurnFlag);

		break;
	}
}


int DrawRasterScroll(const int & X, const int & Y, const double & Cycle, const double & Shake, const int & Time, const int & GrHandle, const bool & isVertical)
{
	int Width = 0, Height = 0;					// Images width & height
	static int result = 0;						// Return only variable

	GetGraphSize(GrHandle, &Width, &Height);

	if(isVertical)
	{
		for (int I = 0; I < Height; ++I)
		{
			const int& DestX = X - Width / 2 + std::cos((I + Time) / 180. * DX_PI * Cycle) * Shake;
			const int& DestY = Y - Height / 2 + I;

			result = DrawRectGraph
				(
					DestX, DestY,
					0, I,
					Width, 1,
					GrHandle,
					TRUE, FALSE
					);
		}
	}
	else
	{
		for (int I = 0; I < Width; ++I)
		{
			const int& DestX = X - Width / 2 + I;
			const int& DestY = Y - Height / 2 + std::cos((I + Time) / 180. * DX_PI * Cycle) * Shake;

			result = DrawRectGraph
				(
					DestX, DestY,
					I, 0,
					1, Height,
					GrHandle,
					TRUE, FALSE
					);
		}
	}

	return result;
}


void DrawCircleScreen(int CenterX, int CenterY, float InRadius, float OutRadius, float Absorption, int ScreenHandle)
{
	float CenterDistance;
	float GraphCenterDistance;
	float AbsorptionDistance;
	float AbsorptionMoveX, AbsorptionMoveY;
	float Angle;
	int TextureW, TextureH;
	float Sin, Cos;
	COLOR_U8 DiffuseColor;
	int i, j;
	VERTEX2D *Vert;
	WORD *Ind;
	float AngleCosTable[CIRCLE_ANGLE_VERTEX_NUM];
	float AngleSinTable[CIRCLE_ANGLE_VERTEX_NUM];
	float InCircleCosTable[CIRCLE_RADIUS_VERTEX_NUM];

	// スタックに積むには大きいので static 配列にしました
	static VERTEX2D Vertex[CIRCLE_RADIUS_VERTEX_NUM * CIRCLE_ANGLE_VERTEX_NUM];
	static WORD Index[CIRCLE_ANGLE_VERTEX_NUM * 6 * (CIRCLE_RADIUS_VERTEX_NUM - 1)];

	// 描画可能画像が使用しているテクスチャのサイズを取得しておく
	GetGraphTextureSize(ScreenHandle, &TextureW, &TextureH);

	// 最初に普通に描画
	DrawGraph(0, 0, ScreenHandle, FALSE);

	// 描画カラーを作成しておく
	DiffuseColor = GetColorU8(255, 255, 255, 255);

	// 外周部分用の Sin, Cos テーブルを作成する
	Angle = 0.0f;
	for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; i++, Angle += DX_PI_F * 2.0f / CIRCLE_ANGLE_VERTEX_NUM)
	{
		AngleSinTable[i] = static_cast<float>( sin((double)Angle) );
		AngleCosTable[i] = static_cast<float>( cos((double)Angle) );
	}

	// 内側の盛り上がっているように見せる箇所で使用する Cos テーブルを作成する
	Angle = 0.0f;
	for (i = 0; i < CIRCLE_RADIUS_VERTEX_NUM; i++, Angle += (DX_PI_F / 2.0f) / (CIRCLE_RADIUS_VERTEX_NUM - 1))
		InCircleCosTable[i] = static_cast<float>( cos((double)Angle) );

	// ポリゴン頂点インデックスの準備
	Ind = Index;
	for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; i++)
	{
		for (j = 0; j < CIRCLE_RADIUS_VERTEX_NUM - 1; j++, Ind += 6)
		{
			Ind[0] = i * CIRCLE_RADIUS_VERTEX_NUM + j;
			Ind[1] = Ind[0] + 1;
			if (i == CIRCLE_ANGLE_VERTEX_NUM - 1)
			{
				Ind[2] = j;
				Ind[3] = j + 1;
			}
			else
			{
				Ind[2] = Ind[0] + CIRCLE_RADIUS_VERTEX_NUM;
				Ind[3] = Ind[0] + 1 + CIRCLE_RADIUS_VERTEX_NUM;
			}
			Ind[4] = Ind[2];
			Ind[5] = Ind[1];
		}
	}

	// バイリニア補間描画にする
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	// 外側のドーナツ部分を描画

	// 中心に向かうにしたがって中心方向にテクスチャ座標をずらす
	Vert = Vertex;
	for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; i++)
	{
		// 使用する Sin, Cos の値をセット
		Sin = AngleSinTable[i];
		Cos = AngleCosTable[i];

		for (j = 0; j < CIRCLE_RADIUS_VERTEX_NUM; j++, Vert++)
		{
			// 円の中心までの距離を算出
			CenterDistance = OutRadius - (OutRadius - InRadius) * j / (CIRCLE_RADIUS_VERTEX_NUM - 1);

			// 中心に引き込まれる距離を算出
			AbsorptionDistance = Absorption * j / (CIRCLE_RADIUS_VERTEX_NUM - 1);

			// 中心に向かって移動する距離を算出
			AbsorptionMoveX = Cos * AbsorptionDistance;
			AbsorptionMoveY = Sin * AbsorptionDistance;

			// スクリーン座標の決定
			Vert->pos.x = Cos * CenterDistance + CenterX;
			Vert->pos.y = Sin * CenterDistance + CenterY;
			Vert->pos.z = 0.0f;

			// テクスチャ座標のセット
			Vert->u = (Vert->pos.x + AbsorptionMoveX) / TextureW;
			Vert->v = (Vert->pos.y + AbsorptionMoveY) / TextureH;

			// その他のパラメータをセット
			Vert->rhw = 1.0f;
			Vert->dif = DiffuseColor;
		}
	}

	// 歪んだドーナツの描画
	DrawPrimitiveIndexed2D(Vertex, _countof(Vertex), Index, _countof(Index), DX_PRIMTYPE_TRIANGLELIST, ScreenHandle, FALSE);

	// 内側の盛り上がっているように見える部分を描画

	// Cosテーブルにしたがってテクスチャ座標をずらす
	Vert = Vertex;
	for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; ++i)
	{
		// 使用する Sin, Cos の値をセット
		Sin = AngleSinTable[i];
		Cos = AngleCosTable[i];

		for (j = 0; j < CIRCLE_RADIUS_VERTEX_NUM; j++, Vert++)
		{
			// 円の中心までの距離を算出
			CenterDistance = InCircleCosTable[j] * InRadius;

			// 画像座標視点での円の中心までの距離を算出
			GraphCenterDistance = ((CIRCLE_RADIUS_VERTEX_NUM - 1) - j) * (Absorption + InRadius) / (CIRCLE_RADIUS_VERTEX_NUM - 1);

			// スクリーン座標の決定
			Vert->pos.x = Cos * CenterDistance + CenterX;
			Vert->pos.y = Sin * CenterDistance + CenterY;
			Vert->pos.z = 0.0f;

			// テクスチャ座標のセット
			Vert->u = (Cos * GraphCenterDistance + CenterX) / TextureW;
			Vert->v = (Sin * GraphCenterDistance + CenterY) / TextureH;

			// その他のパラメータをセット
			Vert->rhw = 1.0f;
			Vert->dif = DiffuseColor;
		}
	}

	// 中心の盛り上がって見える部分を描画
	DrawPrimitiveIndexed2D(Vertex, sizeof(Vertex) / sizeof(VERTEX2D), Index, sizeof(Index) / sizeof(WORD), DX_PRIMTYPE_TRIANGLELIST, ScreenHandle, FALSE);
	SetDrawMode(DX_DRAWMODE_NEAREST);	// ぼやけるのでニアレストに戻す
}

void DrawEllipseScreen(int CenterX, int CenterY, float Radius, int ScreenHandle)
{
	//float CenterDistance;
	//float GraphCenterDistance;
	//float AbsorptionDistance;
	//float AbsorptionMoveX, AbsorptionMoveY;
	//float Angle;
	//int TextureW, TextureH;
	//float Sin, Cos;
	//COLOR_U8 DiffuseColor;
	//int i, j;
	//VERTEX2D *Vert;
	//WORD *Ind;
	//float AngleCosTable[CIRCLE_ANGLE_VERTEX_NUM];
	//float AngleSinTable[CIRCLE_ANGLE_VERTEX_NUM];
	//float InCircleCosTable[CIRCLE_RADIUS_VERTEX_NUM];

	//// スタックに積むには大きいので static 配列にしました
	//static VERTEX2D Vertex[CIRCLE_RADIUS_VERTEX_NUM * CIRCLE_ANGLE_VERTEX_NUM];
	//static WORD Index[CIRCLE_ANGLE_VERTEX_NUM * 6 * (CIRCLE_RADIUS_VERTEX_NUM - 1)];

	//// 描画可能画像が使用しているテクスチャのサイズを取得しておく
	//GetGraphTextureSize(ScreenHandle, &TextureW, &TextureH);

	//// 最初に普通に描画
	//DrawGraph(0, 0, ScreenHandle, FALSE);

	//// 描画カラーを作成しておく
	//DiffuseColor = GetColorU8(255, 255, 255, 255);

	//// 外周部分用の Sin, Cos テーブルを作成する
	//Angle = 0.0f;
	//for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; i++, Angle += DX_PI_F * 2.0f / CIRCLE_ANGLE_VERTEX_NUM)
	//{
	//	AngleSinTable[i] = static_cast<float>(sin((double)Angle));
	//	AngleCosTable[i] = static_cast<float>(cos((double)Angle));
	//}

	//// 内側の盛り上がっているように見せる箇所で使用する Cos テーブルを作成する
	//Angle = 0.0f;
	//for (i = 0; i < CIRCLE_RADIUS_VERTEX_NUM; i++, Angle += (DX_PI_F / 2.0f) / (CIRCLE_RADIUS_VERTEX_NUM - 1))
	//	InCircleCosTable[i] = static_cast<float>(cos((double)Angle));

	//// ポリゴン頂点インデックスの準備
	//Ind = Index;
	//for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; i++)
	//{
	//	for (j = 0; j < CIRCLE_RADIUS_VERTEX_NUM - 1; j++, Ind += 6)
	//	{
	//		Ind[0] = i * CIRCLE_RADIUS_VERTEX_NUM + j;
	//		Ind[1] = Ind[0] + 1;
	//		if (i == CIRCLE_ANGLE_VERTEX_NUM - 1)
	//		{
	//			Ind[2] = j;
	//			Ind[3] = j + 1;
	//		}
	//		else
	//		{
	//			Ind[2] = Ind[0] + CIRCLE_RADIUS_VERTEX_NUM;
	//			Ind[3] = Ind[0] + 1 + CIRCLE_RADIUS_VERTEX_NUM;
	//		}
	//		Ind[4] = Ind[2];
	//		Ind[5] = Ind[1];
	//	}
	//}

	//// バイリニア補間描画にする
	//SetDrawMode(DX_DRAWMODE_BILINEAR);

	//// 外側のドーナツ部分を描画

	//// 中心に向かうにしたがって中心方向にテクスチャ座標をずらす
	//Vert = Vertex;
	//for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; i++)
	//{
	//	// 使用する Sin, Cos の値をセット
	//	Sin = AngleSinTable[i];
	//	Cos = AngleCosTable[i];

	//	for (j = 0; j < CIRCLE_RADIUS_VERTEX_NUM; j++, Vert++)
	//	{
	//		// 円の中心までの距離を算出
	//		CenterDistance = OutRadius - (OutRadius - InRadius) * j / (CIRCLE_RADIUS_VERTEX_NUM - 1);

	//		// 中心に引き込まれる距離を算出
	//		AbsorptionDistance = Absorption * j / (CIRCLE_RADIUS_VERTEX_NUM - 1);

	//		// 中心に向かって移動する距離を算出
	//		AbsorptionMoveX = Cos * AbsorptionDistance;
	//		AbsorptionMoveY = Sin * AbsorptionDistance;

	//		// スクリーン座標の決定
	//		Vert->pos.x = Cos * CenterDistance + CenterX;
	//		Vert->pos.y = Sin * CenterDistance + CenterY;
	//		Vert->pos.z = 0.0f;

	//		// テクスチャ座標のセット
	//		Vert->u = (Vert->pos.x + AbsorptionMoveX) / TextureW;
	//		Vert->v = (Vert->pos.y + AbsorptionMoveY) / TextureH;

	//		// その他のパラメータをセット
	//		Vert->rhw = 1.0f;
	//		Vert->dif = DiffuseColor;
	//	}
	//}

	//// 歪んだドーナツの描画
	//SetDrawBlendMode(DX_BLENDMODE_INVSRC, 100);
	//DrawPrimitiveIndexed2D(Vertex, _countof(Vertex), Index, _countof(Index), DX_PRIMTYPE_TRIANGLELIST, ScreenHandle, FALSE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//// 内側の盛り上がっているように見える部分を描画

	//// Cosテーブルにしたがってテクスチャ座標をずらす
	//Vert = Vertex;
	//for (i = 0; i < CIRCLE_ANGLE_VERTEX_NUM; ++i)
	//{
	//	// 使用する Sin, Cos の値をセット
	//	Sin = AngleSinTable[i];
	//	Cos = AngleCosTable[i];

	//	for (j = 0; j < CIRCLE_RADIUS_VERTEX_NUM; j++, Vert++)
	//	{
	//		// 円の中心までの距離を算出
	//		CenterDistance = InCircleCosTable[j] * InRadius;

	//		// 画像座標視点での円の中心までの距離を算出
	//		GraphCenterDistance = ((CIRCLE_RADIUS_VERTEX_NUM - 1) - j) * (Absorption + InRadius) / (CIRCLE_RADIUS_VERTEX_NUM - 1);

	//		// スクリーン座標の決定
	//		Vert->pos.x = Cos * CenterDistance + CenterX;
	//		Vert->pos.y = Sin * CenterDistance + CenterY;
	//		Vert->pos.z = 0.0f;

	//		// テクスチャ座標のセット
	//		Vert->u = (Cos * GraphCenterDistance + CenterX) / TextureW;
	//		Vert->v = (Sin * GraphCenterDistance + CenterY) / TextureH;

	//		// その他のパラメータをセット
	//		Vert->rhw = 1.0f;
	//		Vert->dif = DiffuseColor;
	//	}
	//}

	//// 中心の盛り上がって見える部分を描画
	////DrawPrimitiveIndexed2D(Vertex, sizeof(Vertex) / sizeof(VERTEX2D), Index, sizeof(Index) / sizeof(WORD), DX_PRIMTYPE_TRIANGLELIST, ScreenHandle, FALSE);
	//SetDrawMode(DX_DRAWMODE_NEAREST);	// ぼやけるのでニアレストに戻す
}
