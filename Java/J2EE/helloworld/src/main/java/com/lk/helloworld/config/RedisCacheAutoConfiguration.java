//package com.lk.helloworld.config;
//
//import org.springframework.boot.autoconfigure.AutoConfigureAfter;
//import org.springframework.boot.autoconfigure.data.redis.RedisAutoConfiguration;
//import org.springframework.context.annotation.Bean;
//import org.springframework.context.annotation.Configuration;
//import org.springframework.data.redis.connection.lettuce.LettuceConnectionFactory;
//import org.springframework.data.redis.core.RedisTemplate;
//import org.springframework.data.redis.serializer.GenericJackson2JsonRedisSerializer;
//import org.springframework.data.redis.serializer.StringRedisSerializer;
//
//import java.io.Serializable;
//
///**
// * RedisTemplate的配置
// */
//@Configuration
//@AutoConfigureAfter(RedisAutoConfiguration.class)
//public class RedisCacheAutoConfiguration {
//
//
//    @Bean
//    public RedisTemplate<String, Serializable> redisCacheTemplate(LettuceConnectionFactory redisConnectionFactory) {
//
//        RedisTemplate<String, Serializable> template = new RedisTemplate<>();
//        // 设置 key 序列化方式，StringRedisSerializer的序列化方式，如果没有设置，key前面会有一段字节。
//        template.setKeySerializer(new StringRedisSerializer());
//        // 设置 value 序列化方式，序列化为 json。
//        template.setValueSerializer(new GenericJackson2JsonRedisSerializer());
//        // 设置连接池
//        template.setConnectionFactory(redisConnectionFactory);
//        return template;
//    }
//}