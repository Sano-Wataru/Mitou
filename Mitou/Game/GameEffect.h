#pragma once

namespace GameEffect
{
	//弾発射時のエフェクト
	struct ShotEffect : IEffect
	{
		Vec2 xy_;
		ColorF color_;

		explicit ShotEffect(const Vec2& xy, ColorF color) : xy_(xy), color_(color)
		{

		}

		bool update(double t) override
		{
			Circle{ xy_, (t * 150) }.draw(color_);

			//秒数以下なら継続
			return (t < 0.07);
		}
	};

	//被弾時のエフェクト
	struct SparkEffect : IEffect
	{
		Vec2 xy_;
		double r_;

		explicit SparkEffect(const Vec2& xy, const double r = 10.0) : xy_(xy), r_(r)
		{

		}

		bool update(double t) override
		{
			const double e = EaseOutQuart(t);

			Circle{ xy_, e * r_ }.drawFrame(r_ / 4.0 * (e - 1.7), ColorF{ 1.0, 0.5, 0.0, 1.0 * (1.0 - pow(e, 1.5)) });
			Circle{ xy_, e * r_ * 0.9 }.drawFrame(r_ / 4.0 * (e - 1.0), ColorF{ 1.0, 0.5 + 0.5 * e, 0.3 * e });
			Circle{ xy_, e * r_ * 0.5 }.draw(ColorF{ 1.0, 1.0, 0.2, 1.0 - e });

			//秒数以下なら継続
			return (t < 1.0);
		}
	};

	//爆破エフェクト
	struct ExplodeEffect : IEffect
	{
		struct Particle
		{
			Vec2 xy_;
			double r_;
			double angle_;
			double speed_;

			Circle circle_;

			explicit Particle(Vec2 xy, const double r, const double angle, const double speed) :
				xy_(xy), r_(r), angle_(angle), speed_(speed), circle_(xy, r)
			{

			}

			void draw()
			{
				//円形描画
				circle_.draw(Palette::White);

				//角度方向に移動
				xy_.x += speed_ * Cos(ToRadians(angle_));
				xy_.y += speed_ * Sin(ToRadians(angle_));

				//円オブジェクトの座標を更新
				circle_.setCenter(xy_);

				//円オブジェクトの半径を更新
				circle_.r *= 0.9;
			}
		};

		Vec2 xy_;
		double r_;
		Array<Particle> particles_;

		explicit ExplodeEffect(const Vec2& xy, const double r, const int32 n) : xy_(xy), r_(r)
		{
			//粒子オブジェクトを初期化
			for (auto i : step(n))
				particles_ << Particle{ xy, Random<double>(0, 10), Random<double>(0, 360),
					Random<double>(1, 10) };
		}

		bool update(double t) override
		{
			const double x = 2 * t * Math::Pi * 0.5;
			const double f = 10 * Sin(x) * pow(Cos(x), 3);

			//円状爆発エフェクト
			Circle{ xy_, t * r_ * 1.6 * f }.draw(ColorF{ 1.0, 0.7, 0.0, 0.1 * f * f });
			Circle{ xy_, t * r_ * 1.3 * f }.draw(ColorF{ 1.0, 0.7, 0.0, 0.3 * f });
			Circle{ xy_, t * r_ * 1.1 * f }.draw(ColorF{ 1.0, 0.7, 0.0, 1.0 });
			Circle{ xy_, t * r_ * f }.draw(ColorF{ 1.0, 1.0, 0.9 });

			//粒子拡散エフェクト
			for (auto i : step(particles_.size()))
				particles_[i].draw();

			return(t < 0.5);
		}
	};

	//破片散らばりエフェクト
	struct CrackEffect : IEffect
	{
		//n多角形を作成する
		struct RPolygon
		{
			int32 n_;

			Array<Vec2> arr;

			Polygon polygon_;

			RPolygon(const Vec2& xy, const double size, const int32 range) : n_(Random<int32>(3, range))
			{
				double sangle = Random<double>(0, Math::TwoPi);
				double angle = sangle;

				for (auto i : step(n_))
				{
					arr << xy + Vec2{ size / 2.0 * Cos(angle), size / 2.0 * Sin(angle) };

					//正n多角形の頂点に乱数で角度を加算してずらす
					angle = sangle + Math::TwoPi / n_ * (i + 1) + Random<double>(-Math::TwoPi / n_ / 2.0, Math::TwoPi / n_ / 2.0);
				}
				polygon_ = Polygon{ arr };
			}

			void draw(const ColorF color)
			{
				polygon_.draw(color);
			}
		};

		//破片オブジェクト
		struct Fragment
		{
			Vec2 xy_;

			double speed_;

			double rotate_;

			double angle_;

			double size_;

			RPolygon polygon_;

			ColorF color_;

			explicit Fragment(Vec2 xy, const double size, const double speed,
				const double angle, const double rotate, const double range, const Color color) :
				xy_(xy), speed_(speed), angle_(angle), size_(size), rotate_(rotate),
				polygon_(Vec2{ 0.0, 0.0 }, size, range), color_(color)
			{

			}

			void draw()
			{
				//座標・角度更新
				polygon_.polygon_.rotated(angle_).movedBy(xy_).draw(color_);

				xy_.x += speed_ * Cos(ToRadians(angle_));
				xy_.y += speed_ * Sin(ToRadians(angle_));

				angle_ += rotate_;

				//アルファ値更新
				color_.a -= speed_ * 0.01;
			}
		};

		Vec2 xy_;

		double r_;

		Array<Fragment> fragments_;

		int32 n_;

		explicit CrackEffect(const Vec2& xy, const double r, const int32 n, const Color color) : xy_(xy), r_(r), n_(n)
		{
			for (auto i : step(n_))
				fragments_ << Fragment{ RandomVec2(Circle{ xy_, r_ }), Random<double>(1, 20),
					Random<double>(0.5, 2), Random<double>(0, 360), Random<double>(0.02, 0.2), 4, color };
		}

		bool update(double t)
		{
			for (auto i : step(n_))
				fragments_[i].draw();

			return (t < 4.0);
		}
	};
}
