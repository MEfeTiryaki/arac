  # Arac_Gazebo
  English version is below.

  Bu paket Gazebo benzetim ortamıyla arayüz niteliği taşımaktadır.
  Benzetilen kulmanın konum, hız, ivme, algılayıcı verilerini yayınlayıp,
  güdümcüden gelen girdileri kulmanın gerekli deviteçlerine iletir.

  Bu arayüz benzetimde kestirimci olması ve olmaması durumunda farklı veriler yayınlar.
  Ve temel olarak gerçek kulmanın sürücleriyle aynı işlevi yerine getirir.

  İleriki sürümlerde buradaki Gazebo eklentileri daha genelgecer bir yapı için Kulman belleğinde
  bulunan eklentilerden kalıtım yoluyla kurgulanacaktır.

  Bu paket aşağıdaki paketlere bağlıdır.
  * boost
  * gazebo
  * param_io
  * azebo_plugins
  * gazebo_ros
  * roscpp
  * urdf
  * xacro
  * arac_msgs


  #### English version

  This package is an interface for Gazebo simulation environment. It publishes position,velocity,acceleration,
  sensor data of simulated robot, and passes the input data coming from controler to the actuators of the robot.

  This interface publish different data if an estimator exists in the system. And it fundamentally mimics the drivers of the real robot.

  In future versions, this Gazebo plugin are going to be inherated from plugin in Kulman repository, to have a more generic structure.

  this package depends following packages;
  * boost
  * gazebo
  * param_io
  * azebo_plugins
  * gazebo_ros
  * roscpp
  * urdf
  * xacro
  * arac_msgs
