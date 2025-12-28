#ifndef SENSOR_H
#define SENSOR_H

#include <inttypes.h>

/**
 *  Direction structure
 */
enum Direction : int8_t {
    CW      = 1,  // clockwise
    CCW     = -1, // counter clockwise
    UNKNOWN = 0   // not yet known or invalid state
};


/**
 *  Pullup configuration structure
 */
enum Pullup : uint8_t {
    USE_INTERN = 0x00, //!< Use internal pullups
    USE_EXTERN = 0x01  //!< Use external pullups
};

/**
*センサーアブストラクトクラスの定義
* 
*このクラスは、あらゆる種類のセンサーのベースとして、意図的にシンプルに保たれます。現在、私たちは持っています
*エンコーダー、磁気エンコーダー、ホールセンサーの実装。この基本クラスは抽出します
*最も基本的な一般的な機能により、FOCドライバーが操作に必要なデータを取得できるようにします。
* 
*独自のセンサーを実装するには、このクラスのサブクラスを作成し、getSensorangle（）を実装します
* 方法。getSensorangle（）は、ラジアンでフロート値を返し、現在のシャフト角を表します
*範囲0〜2* pi（1回のフルターン）。 
* 
*正しく機能するには、センサークラスの更新（）メソッドを十分に迅速に呼び出す必要があります。通常、
* bldcmotorのループフォック（）関数は、反復ごとに1回呼び出すため、loopfoc（）をすばやく呼び出すことを確認する必要があります
*正しいモーターとセンサーの両方の操作のために十分です。
* 
*センサーベースクラスはgetVelocity（）の実装を提供し、カウントの処理を行います
*正確な方法での革命ですが、あなたが望むなら、これらの方法をさらに上書きしてより多くを提供することができます
*ハードウェアの最適な実装。
* 
*/
class Sensor{
	friend class SmoothingSensor;
    public:
        /**
         * 0〜2piの範囲で機械式シャフト角を取得します。この値はできるだけ正確になります
         *ハードウェア。ベース実装は、update（）によって返された値を使用するため、 
         * update（）が再び呼び出されるまで、同じ値が返されます。
         */
        virtual float getMechanicalAngle();

        /**
        *完全な回転とシャフト角を含む電流（RAD）を取得します。
        *ベース実装は、update（）によって返された値を使用するため、同じように
        * update（）が再び呼び出されるまで値が返されます。
        *回転数が増えるにつれて、この値の精度は限られていることに注意してください。
        *フロートの精度が限られているため、フルの大きな角度をキャプチャできないため 
        *回転とシャフト角の小さな角度を同時に。
        */
        virtual float getAngle();
        
        /** 
        *それをサポートするアーキテクチャでは、これは二重精度の位置値を返します、
        *大きな位置値の精度が改善されたはずです。
        *ベース実装は、update（）によって返された値を使用するため、同じように
        * update（）が再び呼び出されるまで値が返されます。
        */
        virtual double getPreciseAngle();

        /** 
        *現在の角速度（rad/s）を取得します
        *サブクラスでオーバーライドできます。基本実装は値を使用します 
        * update（）によって返されたので、update（）の場合にのみこれを呼び出すのは理にかなっています
        *その間に呼び出されました。
        */
        virtual float getVelocity();

        /**
        *フルローテーションの数を取得します
        *ベース実装は、update（）によって返された値を使用するため、同じように
        * update（）が再び呼び出されるまで値が返されます。 
        */
        virtual int32_t getFullRotations();

        /**
        *ハードウェアセンサーを読み取ってセンサー値を更新します。
        *一部の実装は割り込みで動作する場合があり、これは必要ありません。
        *基本実装はgetSensorangle（）を呼び出し、内部を更新します
        *角度、タイムスタンプ、完全回転のフィールド。
        *この方法は、その完全を保証するのに十分頻繁に呼び出さなければなりません
        *回転は、まれな投票のために「見逃されていません」。
        *あなたのために代替行動が必要な場合、サブクラスでオーバーライドします
        *センサーハードウェア。
        */
        virtual void update();

        /** 
        *絶対ゼロを検索する必要がある場合は0を返します
        * 0-磁気センサー（＆インデックス付きエンコーダーが見つかりました）
        * 1-インデックス付きのecoder（インデックスがまだ見つかりません）
        */
        virtual int needsSearch();

        /**
        *速度への更新間の最小時間。経過時間がこれよりも低い場合、速度は更新されません。
        */
        float min_elapsed_time = 0.000100; // default is 100 microseconds, or 10kHz

    protected:
        /** 
        *センサーハードウェアから現在のシャフト角を取得し、 
        * 0〜2piの範囲のラジアンのフロートとして返します。
        * 
        *この方法は純粋な仮想であり、サブクラスに実装する必要があります。
        *この方法を直接呼び出しても、ベースクラスの内部フィールドは更新されません。
        *外部コードから呼び出すときに更新（）を使用します。
        */
        virtual float getSensorAngle()=0;
        /**
        *センサーサブクラスのINITメソッドからセンサー:: init（）を呼び出してくださいスタートアップが必要な場合
        *基本クラスのinit（）メソッドは、内部フィールドを初期化するためにgetSensorangle（）を数回呼び出します
        *現在の値に対して、最初の呼び出し中に不連続性（「ゼロからのジャンプ」）がないことを確認する
        * sensor.getangle（）およびsensor.getvelocity（）へ
        */
        virtual void init();

        // velocity calculation variables
        float velocity=0.0f;
        float angle_prev=0.0f; // result of last call to getSensorAngle(), used for full rotations and velocity
        long angle_prev_ts=0; // timestamp of last call to getAngle, used for velocity
        float vel_angle_prev=0.0f; // angle at last call to getVelocity, used for velocity
        long vel_angle_prev_ts=0; // last velocity calculation timestamp
        int32_t full_rotations=0; // full rotation tracking
        int32_t vel_full_rotations=0; // previous full rotation value for velocity calculation
};

#endif
