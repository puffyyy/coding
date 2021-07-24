//import com.lk.helloworld.HelloworldApplication;
//import com.lk.helloworld.entity.Book;
//import org.junit.Test;
//import org.junit.runner.RunWith;
//import org.slf4j.Logger;
//import org.slf4j.LoggerFactory;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.data.redis.core.RedisTemplate;
//import org.springframework.data.redis.core.StringRedisTemplate;
//import org.springframework.test.context.junit4.SpringRunner;
//
//import java.io.Serializable;
//import java.util.Date;
//import java.util.concurrent.ExecutorService;
//import java.util.concurrent.Executors;
//import java.util.concurrent.TimeUnit;
//
//@RunWith(SpringRunner.class)
//@SpringBootTest(classes = {HelloworldApplication.class})
//public class SpringBootLettuceRedisApplicationTests {
//
//    private static final Logger LOGGER = LoggerFactory.getLogger(SpringBootLettuceRedisApplicationTests.class);
//
//    @Autowired
//    private StringRedisTemplate stringRedisTemplate;
//
//    @Autowired
//    private RedisTemplate<String, Serializable> redisTemplate;
//
//    /**
//     * 测试线程安全
//     */
//    @Test
//    public void testSafe() {
//        // 测试线程安全, 每次都是增加 1000 说明在多线程的时候 redis还是安全的。注意：这里不一定开了1000个线程，全看执行速度怎么样。
//        ExecutorService executorService = Executors.newFixedThreadPool(1000);
//        stringRedisTemplate.opsForValue().set("k0", "0");
//        for (int i = 0; i < 1000; i++) {
//            stringRedisTemplate.opsForValue().increment("k0", 1);
//        }
//        final String k0 = stringRedisTemplate.opsForValue().get("k0");
//        LOGGER.info("[线程安全结果] - [{}]", k0);
//    }
//
//    @Test
//    public void setAndGet() {
//        stringRedisTemplate.opsForValue().set("k1", "v1");
//        final String k1 = stringRedisTemplate.opsForValue().get("k1");
//        LOGGER.info("[字符缓存结果] - [{}]", k1);
//        stringRedisTemplate.opsForValue().set("k2", "v2中文");
//        final String k2 = stringRedisTemplate.opsForValue().get("k2");
//        LOGGER.info("[字符缓存中文结果] - [{}]", k2);
//        // TODO 以下只演示整合，具体Redis命令可以参考官方文档，Spring Data Redis 只是改了个名字而已，Redis支持的命令它都支持
//        String key = "battcn:user:1";
//        redisTemplate.opsForValue().set(key, new Book("1L", "u1中文", new Date(), "a"));
//        // TODO 对应 String（字符串）
//        final Book user = (Book) redisTemplate.opsForValue().get(key);
//        LOGGER.info("[对象缓存结果] - [{}]", user);
//    }
//
//    /**
//     * 设置超时测试
//     */
//    @Test
//    public void testSetAndTimeOut() {
//        // 设置超时时间
//        stringRedisTemplate.opsForValue().set("testTimeOut", "100", 3, TimeUnit.SECONDS);
//        LOGGER.info("[查询结果] - [{}]", stringRedisTemplate.opsForValue().get("testTimeOut"));
//        // 休眠 5 秒后，就超时了，查询不到了。
//        try {
//            Thread.sleep(10000);
//        } catch (InterruptedException e) {
//        }
//        LOGGER.info("[休眠五秒查询结果] - [{}]", stringRedisTemplate.opsForValue().get("testTimeOut"));
//    }
//
//    /**
//     * 移除数据测试
//     */
//    @Test
//    public void testRemove() {
//        redisTemplate.opsForValue().set("removetest", "有数据");
//        LOGGER.info("[查询结果] - [{}]", stringRedisTemplate.opsForValue().get("removetest"));
//        redisTemplate.delete("removetest");
//        LOGGER.info("[删除 key 后查询结果] - [{}]", stringRedisTemplate.opsForValue().get("removetest"));
//    }
//
//}