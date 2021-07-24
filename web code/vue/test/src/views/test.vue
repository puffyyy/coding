<template>
  <div class="about">
    <h1>This is an test page</h1>
    count:{{ $store.state.count }}
    <button v-on:click="increment">inc</button>
  </div>
</template>

<script>
export default {
  methods: {
    increment() {
      this.$store.commit("increment");
    },
  },
};
</script>