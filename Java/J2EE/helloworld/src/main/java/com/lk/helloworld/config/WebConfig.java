package com.lk.helloworld.config;

import com.lk.helloworld.converter.MyConverter;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.MediaType;
import org.springframework.http.converter.HttpMessageConverter;
import org.springframework.web.accept.ContentNegotiationStrategy;
import org.springframework.web.accept.HeaderContentNegotiationStrategy;
import org.springframework.web.accept.ParameterContentNegotiationStrategy;
import org.springframework.web.servlet.config.annotation.ContentNegotiationConfigurer;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.util.*;

@Configuration(proxyBeanMethods = false)
public class WebConfig {
    
    @Bean
    public WebMvcConfigurer webMvcConfigurer() {
        return new WebMvcConfigurer() {
            @Override
            public void extendMessageConverters(List<HttpMessageConverter<?>> converters) {
                converters.add(new MyConverter());
            }
            
            @Override
            public void configureContentNegotiation(ContentNegotiationConfigurer configurer) {
                Map<String, MediaType> map = new HashMap<String, MediaType>() {
                    private static final long serialVersionUID = 1338860583269378925L;
                    
                    {
                        put("default", MediaType.parseMediaType("application/book"));
                        put("json", MediaType.APPLICATION_JSON);
                        put("xml", MediaType.APPLICATION_XML);
                    }
                };
                ParameterContentNegotiationStrategy parameterContentNegotiationStrategy = new ParameterContentNegotiationStrategy(map);
                configurer.strategies(Arrays.asList(
                        parameterContentNegotiationStrategy, new HeaderContentNegotiationStrategy()));
            }
        };
    }
    
}
